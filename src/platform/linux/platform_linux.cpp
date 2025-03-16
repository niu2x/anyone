#include "platform_linux.h"
#include <stdarg.h>

namespace anyone {

void PlatformSupportLinux::log(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    fflush(stdout);
}

} // namespace anyone