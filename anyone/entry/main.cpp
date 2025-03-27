#if defined(ANYONE_TARGET_LINUX)
#include "platform/linux/support.h"
#endif

#if defined(ANYONE_TARGET_DARWIN)
    #include "platform/darwin/support.h"
#endif

#include "main/core.h"
#include "3rd/cxxopts.hpp"

using namespace anyone;

static void run(StartupConfig& config)
{
    Core core;
    core.set_startup_config(config);

    auto platform_support = GET_PLATFORM_SUPPORT();
    platform_support->init_window();
    
    while (platform_support->poll_events()) {
        core.kick_one_frame();
        platform_support->swap_buffers();
    }
}

int main(int argc, char* argv[])
{
    cxxopts::Options options("anyone_rt", "anyone runtime");
    // clang-format off
    options.add_options()
        ("project", "project dir", cxxopts::value<std::string>()->default_value(""))
        ;
    // clang-format on

    auto result = options.parse(argc, argv);
    auto project_dir = result["project"].as<std::string>();
    #if defined(ANYONE_TARGET_LINUX)
    anyone::PlatformLinux platform_impl;
    #endif
#if defined(ANYONE_TARGET_DARWIN)
    anyone::PlatformDarwin platform_impl;
#endif

    StartupConfig config = {
        .platform_support = &platform_impl,
        .project_dir = project_dir,
    };

    run(config);
    return 0;
}