#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "type.h"
// #include "platform.h"

namespace anyone {

class PlatformSupport;

class Core : public Singleton<Core> {
public:
    Core();
    ~Core();

    void set_platform_support(UniquePtr<PlatformSupport> p);
    void set_project_dir(const String& project_dir);

    void start_game();
    void update();
    void render();

    void notify_framebuffer_size_changed(int width, int height);

    PlatformSupport* get_platform_support() const
    {
        return platform_support_.get();
    }

    void dbg_text(int x, int y, const char* xx);

private:
    lua_State* lua_;
    UniquePtr<PlatformSupport> platform_support_;
    Optional<String> project_dir_;

    int framebuffer_width_;
    int framebuffer_height_;

    int load_lua();
    static int lua_loader(lua_State* L);
};

} // namespace anyone