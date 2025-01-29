#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include "source/Application.hpp"

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < false)
    {
        std::cout << "Failed to initialize the SDL3 video\n";
        return -1;
    }

    Application app;

    app.Tick();

    // Clean up SDL.
    SDL_Quit();
    return 0;
}
