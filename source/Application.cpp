#include "Application.hpp"

Application::Application()
{
    passedTime = 0;

    // Window
    m_window = SDL_CreateWindow("Window", 1280, 720, 0);
    if (!m_window)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL3 Error: " << SDL_GetError() << "\n";
        return;
    }

    // Renderer
    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer)
    {
        std::cout << "Failed to create renderer\n";
        std::cout << "SDL3 Error: " << SDL_GetError() << "\n";
        return;
    }
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    RenderComponent = new SpriteSheetRenderComponent(m_renderer, LoadTexture("assets/robosheet.bmp"), {0, 0, 54, 100});

    if(!RenderComponent){
        std::cout << "Failed to create render component\n";
        std::cout << "SDL3 Error: " << SDL_GetError() << "\n";
        return;
    }
}

Application::~Application()
{
    if(RenderComponent){
        delete RenderComponent;
    }

    SDL_DestroyRenderer(m_renderer);
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

        Vector2D newPosition = RenderComponent->GetPosition() + Vector2D(30.0*GetDeltaTime(), 0);

        RenderComponent->SetPosition(newPosition);
        //m_image_x += (5.0 * GetDeltaTime());


        Draw();
    }
}

void Application::Draw()
{
    SDL_RenderClear(m_renderer);
    RenderComponent->Draw(GetDeltaTime());
    SDL_RenderPresent(m_renderer);
}

double Application::GetDeltaTime()
{
    double currentTime = clock() / 1000.0;
    double deltaTime = currentTime - passedTime;
    passedTime = currentTime;
    if(deltaTime <= 0){
        //deltaTime = 0.001;
    }
    std::cout << "Delta: " << deltaTime << std::endl;
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

SDL_Texture *Application::LoadTexture(char const *path)
{
    return SDL_CreateTextureFromSurface(m_renderer, LoadSurface(path));
}
