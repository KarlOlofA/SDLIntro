#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <chrono>

class Application
{

public:

    Application();
    ~Application();

    void Tick();
    void Draw();

    double GetDeltaTime();

    SDL_Surface* LoadSurface(char const *path);

private:

    const double DESIRED_FRAME_TIME = 1.0 / 60.0; 

    double passedTime;

    double m_image_x;
    double m_image_y;

    SDL_Window* m_window;
    SDL_Surface* m_window_surface;
    SDL_Event m_window_event;
    
    SDL_Surface *m_image;
    SDL_Rect     m_image_position;
};