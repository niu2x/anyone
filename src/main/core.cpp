#include "core.h"
#include "platform.h"
#include "../nlohmann/json.hpp"
using json = nlohmann::json;

extern int luaopen_anyone(lua_State* tolua_S);

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