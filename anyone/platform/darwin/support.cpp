#include "main/core.h"
#include "support.h"
#include <stdarg.h>
#include "../common/key_code_convert.h"

namespace anyone {

PlatformDarwin::PlatformDarwin()
: native_window_(nullptr)
, window_flags_(0)
, sdl_renderer_(nullptr)
, render_api_(nullptr)
, running_(true)
{
}

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
        SDL_SetWindowFullscreen(native_window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen(native_window_, 0);
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

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                int key_code = from_SDL_key_code(event.key.keysym.sym);
                KeyboardEvent event = { .type = KeyboardEventType::PRESS,
                                        .key_code = key_code };
                GET_CORE()->notify_keyboard_event(event);
                break;
            }
            case SDL_QUIT: {
                running_ = false;
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
    return running_;
}

IntSize PlatformDarwin::get_framebuffer_size() const
{
    int w, h;
    SDL_GL_GetDrawableSize(native_window_, &w, &h);
    return { w, h };
}
DPI PlatformDarwin::get_dpi() const
{
    float ddpi, hdpi, vdpi;
    int display_index = SDL_GetWindowDisplayIndex(native_window_);
    if (display_index < 0) {
        NX_PANIC("no display_index");
    }

    // 获取显示器的 DPI 信息
    if (SDL_GetDisplayDPI(display_index, &ddpi, &hdpi, &vdpi) != 0) {
        NX_PANIC("get dpi fail");
    }
    return { hdpi, vdpi };
}
bool PlatformDarwin::is_full_screen() const
{
    return SDL_GetWindowFlags(native_window_)
           & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void PlatformDarwin::exit() { running_ = false; }

} // namespace anyone