#include "core.h"
#include "platform.h"
#include "../nlohmann/json.hpp"
using json = nlohmann::json;

namespace anyone {

Core::Core() { lua_ = luaL_newstate(); }

Core::~Core() { lua_close(lua_); }

void Core::update() { }

void Core::render()
{
    // glViewport(0, 0, 1, 1);
    glClearColor(1.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Core::notify_framebuffer_size_changed(int width, int height)
{
    LOG("framebuffer_size_changed %d %d", width, height);
}

void Core::set_platform_support(std::unique_ptr<PlatformSupport> p)
{
    platform_support_ = std::move(p);
}

void Core::set_project_dir(const String& dir) { project_dir_ = dir; }

void Core::start_game()
{
    luaL_openlibs(lua_);
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

    if (luaL_dostring(lua_, "require 'entry'")) {
        const char* error_msg = lua_tolstring(lua_, -1, nullptr);
        LOG("lua error: %s", error_msg);
    }
}

} // namespace anyone