#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
// #include <SDL2/SDL_opengl.h>

#include "platform_linux.h"
#include "core.h"
#include "glad/glad.h"
#include "../../cxxopts.hpp"
// #include <boost/program_options.hpp>
// #include <boost/variant/variant.hpp>
// #include <boost/variant/get.hpp>
// namespace po = boost::program_options;
//
// To compile with gcc:  (tested on Ubuntu 14.04 64bit):
//	 g++ sdl2_opengl.cpp -lSDL2 -lGL
// To compile with msvc: (tested on Windows 7 64bit)
//   cl sdl2_opengl.cpp /I C:\sdl2path\include /link C:\path\SDL2.lib
//   C:\path\SDL2main.lib /SUBSYSTEM:CONSOLE /NODEFAULTLIB:libcmtd.lib
//   opengl32.lib

void handle_window_size_changed(anyone::Core& core, SDL_Window* window)
{
    int framebuffer_width, framebuffer_height;
    SDL_GL_GetDrawableSize(window, &framebuffer_width, &framebuffer_height);
    core.notify_framebuffer_size_changed(framebuffer_width, framebuffer_height);

    float ddpi, hdpi, vdpi;
    int display_index = SDL_GetWindowDisplayIndex(window);
    if (display_index < 0) {
        return;
    }

    // 获取显示器的 DPI 信息
    if (SDL_GetDisplayDPI(display_index, &ddpi, &hdpi, &vdpi) != 0) {
        return;
    }
    // printf("Display DPI: diagonal=%f, horizontal=%f, vertical=%f\n",
    //        ddpi,
    //        hdpi,
    //        vdpi);
    core.notify_dpi_changed(hdpi, vdpi);
}

int main(int argc, char* argv[])
{
    cxxopts::Options options("anyone_rt", "anyone runtime");

    // clang-format off
    options.add_options()
        ("project", "project dir", cxxopts::value<std::string>())
        ;
    // clang-format on

    auto result = options.parse(argc, argv);
    auto project_dir = result["project"].as<std::string>();

    {
        anyone::Core core;

        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
        //                     SDL_GL_CONTEXT_PROFILE_CORE);
        // 启用多重采样
        // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // 4x MSAA

        uint32_t window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
        SDL_Window* window = SDL_CreateWindow(
            "Anyone Game", 0, 0, 256, 256, window_flags);

        core.set_platform_support(
            std::make_unique<anyone::PlatformSupportLinux>(window,
                                                           window_flags));
        core.set_project_dir(project_dir);

        // assert(Window);
        SDL_GLContext context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, context);
        SDL_GL_SetSwapInterval(1);
        gladLoadGL();

        handle_window_size_changed(core, window);

        core.start_game();

        bool running = true;
        bool full_screen = false;
        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_KEYDOWN: {
                        switch (event.key.keysym.sym) {
                            // case SDLK_ESCAPE:
                            //   running = 0;
                            //   break;
                            case 'f':
                                full_screen = !full_screen;
                                GET_PLATFORM_SUPPORT()->set_full_screen(
                                    full_screen);
                                break;
                            default:
                                break;
                        }
                        break;
                    }
                    case SDL_QUIT: {
                        running = false;
                        break;
                    }

                    case SDL_WINDOWEVENT: {
                        switch (event.window.event) {
                            case SDL_WINDOWEVENT_RESIZED:
                            case SDL_WINDOWEVENT_SIZE_CHANGED: {
                                handle_window_size_changed(core, window);
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            core.kick_one_frame();

            SDL_GL_SwapWindow(window);
        }

        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    printf("remain ref object counter: %d\n",
           anyone::Ref::get_object_counter());
    anyone::Ref::dump_alive_objects();
    return 0;
}