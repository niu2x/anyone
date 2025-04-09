#include "key_code_convert.h"
#include <SDL2/SDL.h>

namespace anyone {
int from_SDL_key_code(int sdl_key)
{
    if (sdl_key >= 'a' && sdl_key <= 'z') {
        return KEY_A + sdl_key - 'a';
    }

    switch (sdl_key) {
        case SDLK_ESCAPE:
            return KEY_ESCAPE;
    }

    return KEY_UNKNOWN;
}

int from_SDL_mouse_button(int sdl_button)
{
    switch (sdl_button) {
        case SDL_BUTTON_LEFT:
            return MOUSE_LEFT_BTN;
        case SDL_BUTTON_RIGHT:
            return MOUSE_RIGHT_BTN;
        case SDL_BUTTON_MIDDLE:
            return MOUSE_MIDDLE_BTN;
            // case SDL_BUTTON_X1: return MouseButton::X1;
            // case SDL_BUTTON_X2: return MouseButton::X2;
    }
    return MOUSE_LEFT_BTN;
}

} // namespace anyone