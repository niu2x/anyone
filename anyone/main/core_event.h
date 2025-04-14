#pragma once

#include "input.h"

namespace anyone {

class CoreEventListener {
public:
    CoreEventListener() { }
    virtual ~CoreEventListener() { }

    virtual void on_mouse_move(const MouseMoveEvent&) { }
    virtual void on_mouse_button(const MouseButtonEvent&) { }
    virtual void on_mouse_wheel(const MouseWheelEvent&) { }
    virtual void on_keyboard(const KeyboardEvent&) { }
    virtual void on_frame_update() { }
};

} // namespace anyone