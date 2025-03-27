#pragma once

#include "base/type.h"

namespace anyone {

class RenderAPI {
public:
    virtual ~RenderAPI() = 0;
    virtual void clear() = 0;
};

class PlatformSupport {
public:
    virtual ~PlatformSupport() = 0;

    virtual void init_window() = 0;
    virtual void swap_buffers() = 0;
    virtual bool poll_events() = 0;

    virtual void log(const char* fmt, ...) = 0;
    virtual void set_full_screen(bool full_screen) = 0;

    virtual RenderAPI* get_render_api() = 0;
};

} // namespace anyone