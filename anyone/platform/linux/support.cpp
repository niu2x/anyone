#include "../common/key_code_convert.h"
#include "main/core.h"
#include "support.h"
#include <stdarg.h>
#include "glad/include/glad/glad.h"

namespace anyone {

void handle_window_size_changed(anyone::Core* core, SDL_Window* window)
{
    int framebuffer_width, framebuffer_height;
    SDL_GL_GetDrawableSize(window, &framebuffer_width, &framebuffer_height);
    core->notify_framebuffer_size_changed(framebuffer_width,
                                          framebuffer_height);

    float ddpi, hdpi, vdpi;
    int display_index = SDL_GetWindowDisplayIndex(window);
    if (display_index < 0) {
        return;
    }

    // 获取显示器的 DPI 信息
    if (SDL_GetDisplayDPI(display_index, &ddpi, &hdpi, &vdpi) != 0) {
        return;
    }
    // printf("Display DPI: diagonal=%f, horizontal=%f, vertical=%f\n",
    //        ddpi,
    //        hdpi,
    //        vdpi);
    core->notify_dpi_changed(hdpi, vdpi);
}

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
    gladLoadGL();
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
                int key_code = from_SDL_key_code(event.key.keysym.sym);
                KeyboardEvent event = { .type = KeyboardEventType::PRESS,
                                        .key_code = key_code };
                GET_CORE()->notify_keyboard_event(event);
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
                        handle_window_size_changed(GET_CORE(), native_window_);
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