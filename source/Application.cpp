#include "Application.hpp"

Application::Application()
{
    passedTime = 0;

    m_window = SDL_CreateWindow("Window", 1280, 720, 0);
    if (!m_window)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL3 Error: " << SDL_GetError() << "\n";
        return;
    }

    m_window_surface = SDL_GetWindowSurface(m_window);

    if (!m_window_surface)
    {
        std::cout << "Failed to get window's surface\n";
        std::cout << "SDL3 Error: " << SDL_GetError() << "\n";
        return;
    }

    m_image = LoadSurface("assets/robosheet.bmp");
    m_image_position.x = 0;
    m_image_position.y = 0;
    m_image_position.w = 22;
    m_image_position.h = 43;

    m_image_x = 0;
    m_image_y = 0;

    if (!m_image)
    {
        std::cout << "Failed to load image\n";
        std::cout << "SDL3 Error: " << SDL_GetError() << "\n";
        return;
    }
}

Application::~Application()
{
    SDL_DestroySurface(m_window_surface);
    SDL_DestroyWindow(m_window);
}

void Application::Tick()
{
    bool running = true;
    while (running)
    {

        // Listen to events such as quit
        SDL_Event event;
        if (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            }
        }
        //std::cout << "pos: " << 5 * GetDeltaTime() <<std::endl;

        m_image_x += (5.0 * GetDeltaTime());
        std::cout << "pos: " << m_image_x <<std::endl;
        m_image_position.x = m_image_x;

        Draw();
    }
}

void Application::Draw()
{
    SDL_UpdateWindowSurface(m_window);
    SDL_BlitSurface(m_image, nullptr, m_window_surface, &m_image_position);
}

double Application::GetDeltaTime()
{
    double currentTime = SDL_GetTicks() / 1000.0;
    double deltaTime = currentTime - passedTime;
    passedTime = currentTime;
    return deltaTime;
}

SDL_Surface *Application::LoadSurface(char const *path)
{
    SDL_Surface *image_surface = SDL_LoadBMP(path);

    if (!image_surface)
    {
        std::cout << "Failed to load: " << path << std::endl;
        std::cout << SDL_GetError() << std::endl;

        return 0;
    }

    return image_surface;
}
