#pragma once

#include "base/type.h"

namespace anyone {

enum {
    KEY_UNKNOWN = -1,
    KEY_A = 65,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_ESCAPE,
};

enum class KeyboardEventType {
    PRESS,
    RELEASE,
};

struct KeyboardEvent {
    KeyboardEventType type;
    int key_code;
};

} // namespace anyone