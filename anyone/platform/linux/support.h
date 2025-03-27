#pragma once

#include <SDL2/SDL.h>
#include "platform/api/support.h"

namespace anyone {

class PlatformLinux : public PlatformSupport {
public:
    PlatformLinux();
    ~PlatformLinux();

    void init_window() override;
    void log(const char* fmt, ...) override;
    void set_full_screen(bool full_screen) override;

    void swap_buffers() override;
    bool poll_events() override;

private:
    SDL_Window* native_window_;
    SDL_GLContext gl_context_;
    uint32_t window_flags_;
};

} // namespace anyone