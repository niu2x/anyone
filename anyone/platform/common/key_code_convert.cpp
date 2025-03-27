#include "key_code_convert.h"
#include <SDL2/SDL.h>

namespace anyone {
int from_SDL_key_code(int code)
{
    if (code >= 'a' && code <= 'z') {
        return KEY_A + code - 'a';
    }
    return KEY_UNKNOWN;
}
} // namespace anyone