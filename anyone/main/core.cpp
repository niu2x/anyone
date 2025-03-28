#include "core.h"
#include "rml_ui.h"
// #include "gl.h"
// #include "ttf.h"
// #include "dbg_text.h"
// #include "embed/default_ttf.h"
#include "3rd/nlohmann/json.hpp"
#include <sstream>

using json = nlohmann::json;

extern int luaopen_anyone(lua_State* tolua_S);

namespace anyone {

Core::Core()
: platform_support_(nullptr)
, render_api_(nullptr)

, rml_ui_(nullptr)

, project_dir_(std::nullopt)
, dpi_ { 90, 90 }
, framebuffer_size_ { 1, 1 }
, lua_(nullptr)

{
    lua_ = luaL_newstate();
}

Core::~Core()
{
    lua_close(lua_);

    rml_ui_.reset();

    render_api_ = nullptr;
    platform_support_ = nullptr;
    // dbg_text_.reset();
    // dbg_font_.reset();
    // ft_library_.reset();
}

void Core::set_startup_config(const StartupConfig& config)
{
    set_project_dir(config.project_dir);
    set_platform_support(config.platform_support);
}

void Core::notify_render_api_ready()
{
    notify_framebuffer_size_changed();
    notify_dpi_changed();

    render_api_->set_clear_color(Color::BLUE);
    rml_ui_ = std::make_unique<RML_UI>();
}

void Core::update() { }

void Core::render()
{
    render_api_->clear();
    rml_ui_->render();
    // dbg_printf(0, 0, "FPS: %.2f", frame_stats_.avg_fps);
    // dbg_text_->render();
}

void Core::notify_framebuffer_size_changed()
{
    framebuffer_size_ = platform_support_->get_framebuffer_size();
    if (rml_ui_) {
        rml_ui_->notify_framebuffer_size_changed();
    }
}

void Core::notify_dpi_changed() { dpi_ = platform_support_->get_dpi(); }

void Core::set_platform_support(PlatformSupport* p)
{
    platform_support_ = p;

    NX_ASSERT(render_api_ == nullptr, "already had render_api_");
    render_api_ = p->get_render_api();
    if (render_api_) {
        notify_render_api_ready();
        auto dpi = platform_support_->get_dpi();
        LOG("DPI h:%f v:%f", dpi.hori, dpi.vert);
    }
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
    // frame_stats_.frame_start = time_now();

    render();
    update();

    // frame_stats_.frame_stop = time_now();
    // frame_stats_.duration_cache.push_back(
    //     time_diff(frame_stats_.frame_start, frame_stats_.frame_stop));
    // frame_stats_.avg_duration = frame_stats_.duration_cache.get_avg();
    // frame_stats_.avg_fps = 1000 / frame_stats_.avg_duration;
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

// void Core::run_project()
// {
//     if (!project_dir_) {
//         NX_PANIC("no project_dir");
//     }
//     auto config_path = fs::join_path(*project_dir_, "project.json");

//     fs::File config_file(config_path);
//     if (!config_file.open_read()) {
//         NX_PANIC("open file fail: %s", config_path.c_str());
//     }

//     auto read_result = config_file.read_all();

//     if (std::holds_alternative<IO_Error>(read_result)) {
//         NX_PANIC("read file fail: %s", config_path.c_str());
//     }
//     auto bytes = std::get<ByteBuffer>(std::move(read_result));
//     json config = json::parse(bytes);
//     auto entry = config["entry"].get<String>();
//     LOG("entry: %s", entry.c_str());

//     std::stringstream ss;
//     ss << "require '";
//     ss << entry;
//     ss << "'";

//     if (luaL_dostring(lua_, ss.str().c_str())) {
//         const char* error_msg = lua_tolstring(lua_, -1, nullptr);
//         LOG("lua error: %s", error_msg);
//     }
// }

// void Core::start_game()
// {
//     check_gl_version();
//     set_global_gl_state();

//     ft_library_ = std::make_unique<FreeTypeLibrary>();
//     dbg_font_ = std::make_unique<Font>(512, 512, 32);
//     dbg_font_->build_ascii_chars(default_ttf, default_ttf_length);

//     dbg_text_ = std::make_unique<DebugText>(dbg_font_.get());

//     init_lua();

//     run_project();
// }

// void Core::dbg_printf(int x, int y, const char* fmt, ...)
// {
//     va_list args;
//     va_start(args, fmt);
//     dbg_text_->vprintf(x, y, fmt, args);
//     va_end(args);
// }

// void Core::add_framebuffer_size_listener(FramebufferSizeListener* l)
// {
//     framebuffer_size_event_.add_listener(l);
// }

// void Core::remove_framebuffer_size_listener(FramebufferSizeListener* l)
// {
//     framebuffer_size_event_.remove_listener(l);
// }

// void Core::fire_framebuffer_size_changed()
// {
//     framebuffer_size_event_.dispatch(
//         &FramebufferSizeListener::on_framebuffer_size_changed);
// }

void Core::notify_keyboard_event(const KeyboardEvent& event)
{
    if (event.type == KeyboardEventType::PRESS) {
        if (event.key_code == KEY_F) {
            static bool full_screen = false;
            full_screen = !full_screen;
            platform_support_->set_full_screen(full_screen);
        }
    }
}

} // namespace anyone
