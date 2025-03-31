#include "../common/key_code_convert.h"
#include "main/core.h"
#include "support.h"
#include <stdarg.h>
#include "glad/include/glad/glad.h"

namespace anyone {

void handle_window_size_changed(anyone::Core* core, SDL_Window* window)
{
    core->notify_framebuffer_size_changed();
    core->notify_dpi_changed();
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
        SDL_SetWindowFullscreen(native_window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen(native_window_, 0);
    }
}

bool PlatformLinux::is_full_screen() const
{
    return SDL_GetWindowFlags(native_window_)
           & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void PlatformLinux::init_window()
{
    NX_ASSERT(native_window_ == nullptr, "Already exist native_window_");

    window_flags_ = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    native_window_ = SDL_CreateWindow(
        "Anyone Game", 0, 0, 512, 256, window_flags_);

    gl_context_ = SDL_GL_CreateContext(native_window_);
    SDL_GL_MakeCurrent(native_window_, gl_context_);
    SDL_GL_SetSwapInterval(1);
    gladLoadGL();

    glDisable(GL_MULTISAMPLE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_BLEND);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
}

void PlatformLinux::swap_buffers()
{
    if (native_window_) {
        SDL_GL_SwapWindow(native_window_);
    }
}

DPI PlatformLinux::get_dpi() const
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

IntSize PlatformLinux::get_framebuffer_size() const
{
    int w, h;
    SDL_GL_GetDrawableSize(native_window_, &w, &h);
    return { w, h };
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
                        auto size = get_framebuffer_size();
                        glViewport(0, 0, size.width, size.height);
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
