#pragma once

#include "platform.h"
#include <SDL2/SDL.h>

namespace anyone {

class PlatformSupportLinux : public PlatformSupport {
public:
    PlatformSupportLinux(SDL_Window* window, uint32_t window_flags);
    ~PlatformSupportLinux() { }

    void log(const char* fmt, ...) override;
    char get_path_separator() const override;
    void set_full_screen(bool full_screen) override;

private:
    SDL_Window* native_window_;
    uint32_t window_flags_;
};

} // namespace anyone