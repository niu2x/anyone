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

    MOUSE_LEFT_BTN,
    MOUSE_MIDDLE_BTN,
    MOUSE_RIGHT_BTN,

};

enum class KeyboardEventType {
    PRESS,
    RELEASE,
};

struct KeyboardEvent {
    KeyboardEventType type;
    int key_code;
    bool repeat;
};

struct MouseMoveEvent {
    int x, y;
    int rel_x, rel_y;
};

enum class MouseButtonEventType {
    PRESS,
    RELEASE,
};

struct MouseButtonEvent {
    MouseButtonEventType type;
    int x, y;
    int button;
};

enum class MouseWheelDirection {
    NORMAL,
    FLIPPED,
};

struct MouseWheelEvent {
    int x, y;
    MouseWheelDirection direction;
};

} // namespace anyone