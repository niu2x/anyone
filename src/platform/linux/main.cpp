#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
// #include <SDL2/SDL_opengl.h>

#include "core.h"
#include "glad/glad.h"

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

int main(int ArgCount, char** Args)
{

    anyone::Core core;

    uint32_t window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    SDL_Window* window = SDL_CreateWindow(
        "Anyone Game", 0, 0, 256, 256, window_flags);
    // assert(Window);
    SDL_GLContext Context = SDL_GL_CreateContext(window);

    gladLoadGL();

    bool running = true;
    bool full_screen = false;
    while (running) {
        SDL_Event Event;
        while (SDL_PollEvent(&Event)) {
            if (Event.type == SDL_KEYDOWN) {
                switch (Event.key.keysym.sym) {
                    // case SDLK_ESCAPE:
                    //   running = 0;
                    //   break;
                    case 'f':
                        full_screen = !full_screen;
                        if (full_screen) {
                            SDL_SetWindowFullscreen(
                                window,
                                window_flags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                        } else {
                            SDL_SetWindowFullscreen(window, window_flags);
                        }
                        break;
                    default:
                        break;
                }
            } else if (Event.type == SDL_QUIT) {
                running = false;
            }
        }

        core.update();
        core.render();

        SDL_GL_SwapWindow(window);
    }
    return 0;
}