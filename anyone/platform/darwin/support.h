#pragma once

#include <SDL2/SDL.h>
#include "platform/api/support.h"

namespace anyone {

class Metal_API : public RenderAPI {
public:
    Metal_API(SDL_Renderer *sdl_renderer);
    ~Metal_API();
    void clear() override;

private:
    void *pimp_;
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

    RenderAPI* get_render_api() override { return render_api_; }

private:
    SDL_Window* native_window_;
    SDL_Renderer *sdl_renderer_;
    uint32_t window_flags_;
    Metal_API *render_api_;
};

} // namespace anyone