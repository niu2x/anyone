#include "platform/linux/support.h"

using namespace anyone;

static void run(PlatformSupport* platform_support)
{
    platform_support->init_window();
    while (platform_support->poll_events()) {
        platform_support->swap_buffers();
    }
}

int main()
{
    anyone::PlatformLinux platform_linux;
    run(&platform_linux);
    return 0;
}