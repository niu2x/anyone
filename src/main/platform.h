#pragma once

#include <nx/alias.h>
#include "core.h"

#if defined(ANYONE_TARGET_LINUX)
    #include "../platform/linux/glad/include/glad/glad.h"
#endif

// namespace anyone {

// class OpenglLoader {
// public:
// 	virtual ~OpenglLoader() {}
// 	virtual bool load_opengl() = 0;
// };

// }

#define GET_CORE()             anyone::Core::get_singleton_ptr()
#define GET_PLATFORM_SUPPORT() ((GET_CORE())->get_platform_support())

#define LOG(...) (GET_PLATFORM_SUPPORT())->log(__VA_ARGS__)

namespace anyone {
class PlatformSupport {
public:
    virtual ~PlatformSupport() = 0;
    virtual void log(const char* fmt, ...) = 0;
    virtual void set_full_screen(bool full_screen) = 0;
};
} // namespace anyone