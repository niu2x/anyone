#include "support.h"
#include <stdarg.h>

namespace anyone {

PlatformLinux::PlatformLinux() : native_window_(nullptr), window_flags_(0) { }

PlatformLinux::~PlatformLinux()
{
    if (native_window_) {
        SDL_GL_DeleteContext(gl_context_);
        SDL_DestroyWindow(native_window_);
        SDL_Quit();
    }
}

void PlatformLinux::log(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);

    fflush(stdout);
}

void PlatformLinux::set_full_screen(bool full_screen)
{
    if (full_screen) {
        SDL_SetWindowFullscreen(native_window_,
                                window_flags_ | SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen(native_window_, window_flags_);
    }
}

void PlatformLinux::init_window()
{
    NX_ASSERT(native_window_ == nullptr, "Already exist native_window_");

    window_flags_ = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    native_window_ = SDL_CreateWindow(
        "Anyone Game", 0, 0, 256, 256, window_flags_);

    gl_context_ = SDL_GL_CreateContext(native_window_);
    SDL_GL_MakeCurrent(native_window_, gl_context_);
    SDL_GL_SetSwapInterval(1);
}
void PlatformLinux::swap_buffers()
{
    if (native_window_) {
        SDL_GL_SwapWindow(native_window_);
    }
}
bool PlatformLinux::poll_events()
{
    bool running = true;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    // case SDLK_ESCAPE:
                    //   running = 0;
                    //   break;
                    case 'f':
                        // full_screen = !full_screen;
                        // GET_PLATFORM_SUPPORT()->set_full_screen(full_screen);
                        break;
                    default:
                        break;
                }
                break;
            }
            case SDL_QUIT: {
                running = false;
                break;
            }

            case SDL_WINDOWEVENT: {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                    case SDL_WINDOWEVENT_SIZE_CHANGED: {
                        // handle_window_size_changed(core, window);
                        break;
                    }
                }
                break;
            }
        }
    }
    return running;
}

} // namespace anyone