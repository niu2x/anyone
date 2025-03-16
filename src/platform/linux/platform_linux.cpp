#include "platform_linux.h"
#include <stdarg.h>

namespace anyone {

void PlatformSupportLinux::log(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);

    fflush(stdout);
}

char PlatformSupportLinux::get_path_separator() const { return '/'; }

} // namespace anyone