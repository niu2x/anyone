#include "core.h"
#include "platform.h"
#include "gl.h"
#include "ttf.h"
#include "embed/default_ttf.h"
#include "../nlohmann/json.hpp"
#include <sstream>

using json = nlohmann::json;

extern int luaopen_anyone(lua_State* tolua_S);

// Shader sources

const char* vertex_source = R"(
    #version 330 core
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec2 uv;
    out vec2 v_uv;
    void main() {
        gl_Position = vec4(position, 1.0);
        v_uv = uv;
    }

)";

const char* fragment_source = R"(
    #version 330 core
    uniform sampler2D tex;
    in vec2 v_uv;
    out vec4 color;
    void main() {
        color = texture(tex, v_uv);
    }
)";

namespace anyone {

Core::Core() : framebuffer_width_(0), framebuffer_height_(0), dpi_ { 90, 90 }
{
    lua_ = luaL_newstate();
}

Core::~Core()
{
    delete test_program_;
    delete test_vertex_buffer_;
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

    test_vertex_buffer_->bind();
    test_program_->use();

    // dbg_font_->build_ascii_chars(default_ttf, default_ttf_length);
    auto texture = dbg_font_->get_texture();

    // auto texture = new GL_Texture2D(framebuffer_width_, framebuffer_height_);
    // texture->alloc_cpu_buffer();

    // uint32_t* pixel_buffer = (uint32_t*)texture->get_cpu_buffer();

    // for (int x = 0; x < 512; x++) {
    //     for (int y = 0; y < 512; y++) {
    //         if (((x / 32) % 2 == 1) ^ ((y / 32) % 2 == 1))
    //             pixel_buffer[y * 512 + x] = 0xFF000000;
    //         else {
    //             pixel_buffer[y * 512 + x] = 0xFFFFFFFF;
    //         }
    //     }
    // }

    // texture->apply();
    // texture->free_cpu_buffer();

    texture->bind(0);
    test_program_->set_uniform_texture("tex", 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    // delete texture;
    // delete program;
    // delete vertex_buffer;

    // GLenum err;
    // while ((err = glGetError()) != GL_NO_ERROR) {
    //     LOG("opengl error");
    // }
}

void Core::notify_framebuffer_size_changed(int width, int height)
{
    framebuffer_width_ = width;
    framebuffer_height_ = height;
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

    auto file_path = path_join(*project_dir_, "src");
    file_path = path_join(file_path, String(mod_name) + ".lua");

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

void Core::start_game()
{
    LOG("OpenGL version: %s\n", glGetString(GL_VERSION));

    set_global_gl_state();

    ft_library_ = std::make_unique<FreeTypeLibrary>();
    dbg_font_ = std::make_unique<Font>(512, 512, 32);
    dbg_font_->build_ascii_chars(default_ttf, default_ttf_length);

    struct PosXYZ {
        float x, y, z;
        float u, v;
    };

    test_vertex_buffer_ = new GL_VertexBuffer(120);
    test_vertex_buffer_->alloc_cpu_buffer();
    PosXYZ* pos_list = (PosXYZ*)test_vertex_buffer_->get_cpu_buffer();

    pos_list[0] = { -1, -1, 0, 0, 0 };
    pos_list[1] = { 1, -1, 0, 1, 0 };
    pos_list[2] = { 1, 1, 0, 1, 1 };

    pos_list[3] = { -1, -1, 0, 0, 0 };
    pos_list[4] = { 1, 1, 0, 1, 1 };
    pos_list[5] = { -1, 1, 0, 0, 1 };

    test_vertex_buffer_->apply();
    test_vertex_buffer_->free_cpu_buffer();
    test_vertex_buffer_->set_vertex_layout(
        { VertexAttr::POSITION_XYZ, VertexAttr::UV });

    test_program_ = new GL_Program();
    test_program_->attach_shader(GL_Program::ShaderType::VERTEX, vertex_source);
    test_program_->attach_shader(GL_Program::ShaderType::FRAGMENT,
                                 fragment_source);
    test_program_->compile();

    luaL_openlibs(lua_);

    luaopen_anyone(lua_);

    lua_pushcfunction(lua_, lua_loader);
    lua_setglobal(lua_, "__native_lua_loader");
    luaL_dostring(lua_, R"RAW(
    	package.searchers = {__native_lua_loader}
    )RAW");

    if (!project_dir_) {
        NX_PANIC("no project_dir");
    }
    auto config_path = path_join(*project_dir_, "project.json");

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

void Core::dbg_text(int x, int y, const char* xx) { }

} // namespace anyone