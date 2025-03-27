#pragma once

#include <SDL2/SDL.h>
#include "platform/api/support.h"

namespace anyone {

class OpenGL_API : public RenderAPI {
public:
    OpenGL_API();
    ~OpenGL_API();
    void clear() override;
};

class PlatformDarwin : public PlatformSupport {
public:
    PlatformDarwin();
    ~PlatformDarwin();

    void init_window() override;
    void log(const char* fmt, ...) override;
    void set_full_screen(bool full_screen) override;

    void swap_buffers() override;
    bool poll_events() override;

    RenderAPI* get_render_api() override { return &render_api_; }

private:
    SDL_Window* native_window_;
    SDL_GLContext gl_context_;
    uint32_t window_flags_;
    OpenGL_API render_api_;
};

} // namespace anyone