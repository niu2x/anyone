#include "platform/linux/support.h"
#include "main/core.h"

using namespace anyone;

static void run(PlatformSupport* platform_support)
{
    Core core;
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