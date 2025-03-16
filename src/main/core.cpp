#include "core.h"
#include "platform.h"

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
    LOG("framebuffer_size_changed %d %d\n", width, height);
}

void Core::set_platform_support(std::unique_ptr<PlatformSupport> p)
{
    platform_support_ = std::move(p);
}

} // namespace anyone