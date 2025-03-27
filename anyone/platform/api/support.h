#pragma once

#include "base/type.h"

namespace anyone {

class PlatformSupport {
public:
    virtual ~PlatformSupport() = 0;

    virtual void init_window() = 0;
    virtual void swap_buffers() = 0;
    virtual bool poll_events() = 0;

    virtual void log(const char* fmt, ...) = 0;
    virtual void set_full_screen(bool full_screen) = 0;
};

} // namespace anyone