#include "main/core.h"
#include "support.h"
#include <stdarg.h>
#include "../common/key_code_convert.h"

namespace anyone {

PlatformDarwin::PlatformDarwin() : native_window_(nullptr), window_flags_(0),sdl_renderer_(nullptr),render_api_(nullptr) { }

PlatformDarwin::~PlatformDarwin()
{
    if (native_window_) {
        delete render_api_;
        render_api_ = nullptr;
        SDL_DestroyRenderer(sdl_renderer_);
        SDL_DestroyWindow(native_window_);
        SDL_Quit();
    }
}

void PlatformDarwin::log(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);

    fflush(stdout);
}

void PlatformDarwin::set_full_screen(bool full_screen)
{
    if (full_screen) {
        SDL_SetWindowFullscreen(native_window_,
                                window_flags_ | SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen(native_window_, window_flags_);
    }
}

void PlatformDarwin::init_window()
{
    NX_ASSERT(native_window_ == nullptr, "Already exist native_window_");

    window_flags_ = SDL_WINDOW_RESIZABLE|SDL_WINDOW_METAL;
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
    native_window_ = SDL_CreateWindow(
        "Anyone Game", 0, 0, 256, 256, window_flags_);

    sdl_renderer_ = SDL_CreateRenderer(native_window_, -1, SDL_RENDERER_PRESENTVSYNC);
    render_api_ = new Metal_API(sdl_renderer_);
}
void PlatformDarwin::swap_buffers()
{
    if (native_window_) { }
}
bool PlatformDarwin::poll_events()
{
    bool running = true;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                int key_code = from_SDL_key_code(event.key.keysym.sym);
                GET_CORE()->notify_keyboard_event(
                    { .type = KeyboardEventType::PRESS, .key_code = key_code });
                // switch (event.key.keysym.sym) {
                //     // case SDLK_ESCAPE:
                //     //   running = 0;
                //     //   break;
                //     case 'f':
                //         // full_screen = !full_screen;
                //         //
                //         GET_PLATFORM_SUPPORT()->set_full_screen(full_screen);
                //         break;
                //     default:
                //         break;
                // }

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