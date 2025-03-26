#include "platform_linux.h"
#include <stdarg.h>

namespace anyone {

void PlatformSupportLinux::log(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);

    fflush(stdout);
}

void PlatformSupportLinux::set_full_screen(bool full_screen)
{
    if (full_screen) {
        SDL_SetWindowFullscreen(native_window_,
                                window_flags_ | SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen(native_window_, window_flags_);
    }
}

PlatformSupportLinux::PlatformSupportLinux(SDL_Window* window,
                                           uint32_t window_flags)
: native_window_(window)
, window_flags_(window_flags)
{
}

} // namespace anyone