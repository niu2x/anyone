#include "core.h"
#include "platform.h"
#include "gl.h"
#include "ttf.h"
#include "dbg_text.h"
#include "embed/default_ttf.h"
#include "../nlohmann/json.hpp"
#include <sstream>

using json = nlohmann::json;

extern int luaopen_anyone(lua_State* tolua_S);

// Shader sources

// const char* vertex_source = R"(
//     #version 330 core
//     layout(location = 0) in vec3 position;
//     layout(location = 1) in vec2 uv;
//     out vec2 v_uv;
//     void main() {
//         gl_Position = vec4(position, 1.0);
//         v_uv = uv;
//     }

// )";

// const char* fragment_source = R"(
//     #version 330 core
//     uniform sampler2D tex;
//     in vec2 v_uv;
//     out vec4 color;
//     void main() {
//         color = texture(tex, v_uv);
//     }
// )";

namespace anyone {

Core::Core() : framebuffer_width_(0), framebuffer_height_(0), dpi_ { 90, 90 }
{
    lua_ = luaL_newstate();
}

Core::~Core()
{
    dbg_text_.reset();
    lua_close(lua_);
    dbg_font_.reset();
    ft_library_.reset();
    platform_support_.reset();
}

void Core::update() { }

void Core::render()
{
    glViewport(0, 0, framebuffer_width_, framebuffer_height_);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    dbg_printf(0, 0, "FPS: %.2f", frame_stats_.avg_fps);
    dbg_text_->render();
}

void Core::notify_framebuffer_size_changed(int width, int height)
{
    framebuffer_width_ = width;
    framebuffer_height_ = height;

    fire_framebuffer_size_changed();
}

void Core::notify_dpi_changed(float hdpi, float vdpi)
{
    dpi_.hori = hdpi;
    dpi_.vert = vdpi;
}

void Core::set_platform_support(std::unique_ptr<PlatformSupport> p)
{
    platform_support_ = std::move(p);
}

void Core::set_project_dir(const String& dir) { project_dir_ = dir; }

int Core::lua_loader(lua_State* L) { return GET_CORE()->load_lua(); }

int Core::load_lua()
{
    auto mod_name = luaL_optstring(lua_, -1, "");
    printf("lua_loader %s\n", mod_name);

    if (!project_dir_) {
        LOG("no project_dir");
        return 0;
    }

    auto file_path = fs::join_path(*project_dir_, "src");
    file_path = fs::join_path(file_path, String(mod_name) + ".lua");

    fs::File lua_file(file_path);
    if (!lua_file.open_read()) {
        LOG("open file fail: %s", file_path.c_str());
        return 0;
    }

    auto read_result = lua_file.read_all();

    if (std::holds_alternative<IO_Error>(read_result)) {
        LOG("read file fail: %s", file_path.c_str());
        return 0;
    }
    auto bytes = std::get<ByteBuffer>(std::move(read_result));
    auto buf_ptr = (const char*)bytes.data();
    auto buf_len = bytes.size();
    auto ret = luaL_loadbuffer(lua_, buf_ptr, buf_len, mod_name);
    if (ret != LUA_OK) {
        LOG("luaL_loadbuffer fail: %s", lua_tolstring(lua_, -1, nullptr));
        return 0;
    }
    return 1;
}

void Core::kick_one_frame()
{
    frame_stats_.frame_start = time_now();

    render();
    update();

    frame_stats_.frame_stop = time_now();
    frame_stats_.duration_cache.push_back(
        time_diff(frame_stats_.frame_start, frame_stats_.frame_stop));
    frame_stats_.avg_duration = frame_stats_.duration_cache.get_avg();
    frame_stats_.avg_fps = 1000 / frame_stats_.avg_duration;
}

void Core::init_lua()
{
    luaL_openlibs(lua_);

    luaopen_anyone(lua_);

    lua_pushcfunction(lua_, lua_loader);
    lua_setglobal(lua_, "__native_lua_loader");
    luaL_dostring(lua_, R"RAW(
        package.searchers = {__native_lua_loader}
    )RAW");
}

void Core::run_project()
{
    if (!project_dir_) {
        NX_PANIC("no project_dir");
    }
    auto config_path = fs::join_path(*project_dir_, "project.json");

    fs::File config_file(config_path);
    if (!config_file.open_read()) {
        NX_PANIC("open file fail: %s", config_path.c_str());
    }

    auto read_result = config_file.read_all();

    if (std::holds_alternative<IO_Error>(read_result)) {
        NX_PANIC("read file fail: %s", config_path.c_str());
    }
    auto bytes = std::get<ByteBuffer>(std::move(read_result));
    json config = json::parse(bytes);
    auto entry = config["entry"].get<String>();
    LOG("entry: %s", entry.c_str());

    std::stringstream ss;
    ss << "require '";
    ss << entry;
    ss << "'";

    if (luaL_dostring(lua_, ss.str().c_str())) {
        const char* error_msg = lua_tolstring(lua_, -1, nullptr);
        LOG("lua error: %s", error_msg);
    }
}

void Core::start_game()
{
    check_gl_version();
    set_global_gl_state();

    ft_library_ = std::make_unique<FreeTypeLibrary>();
    dbg_font_ = std::make_unique<Font>(512, 512, 32);
    dbg_font_->build_ascii_chars(default_ttf, default_ttf_length);

    dbg_text_ = std::make_unique<DebugText>(dbg_font_.get());

    init_lua();

    run_project();
}

void Core::dbg_printf(int x, int y, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    dbg_text_->vprintf(x, y, fmt, args);
    va_end(args);
}

void Core::add_framebuffer_size_listener(FramebufferSizeListener* l)
{
    framebuffer_size_event_.add_listener(l);
}

void Core::remove_framebuffer_size_listener(FramebufferSizeListener* l)
{
    framebuffer_size_event_.remove_listener(l);
}

void Core::fire_framebuffer_size_changed()
{
    framebuffer_size_event_.dispatch(
        &FramebufferSizeListener::on_framebuffer_size_changed);
}

} // namespace anyone