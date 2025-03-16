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

    void update();
    void render();

    void notify_framebuffer_size_changed(int width, int height);
    void set_platform_support(std::unique_ptr<PlatformSupport> p);

    PlatformSupport* get_platform_support() const
    {
        return platform_support_.get();
    }

private:
    lua_State* lua_;
    std::unique_ptr<PlatformSupport> platform_support_;
};

} // namespace anyone