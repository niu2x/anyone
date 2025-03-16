#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>

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

    anyone::Core core;
    core.set_platform_support(std::make_unique<anyone::PlatformSupportLinux>());
    core.set_project_dir(project_dir);

    uint32_t window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    SDL_Window* window = SDL_CreateWindow(
        "Anyone Game", 0, 0, 256, 256, window_flags);
    // assert(Window);
    SDL_GLContext Context = SDL_GL_CreateContext(window);

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
                            if (full_screen) {
                                SDL_SetWindowFullscreen(
                                    window,
                                    window_flags
                                        | SDL_WINDOW_FULLSCREEN_DESKTOP);
                            } else {
                                SDL_SetWindowFullscreen(window, window_flags);
                            }
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

        core.update();
        core.render();

        SDL_GL_SwapWindow(window);
    }
    return 0;
}