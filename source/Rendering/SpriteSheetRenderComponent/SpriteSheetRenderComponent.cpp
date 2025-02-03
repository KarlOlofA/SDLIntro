#include "SpriteSheetRenderComponent.hpp"

SpriteSheetRenderComponent::SpriteSheetRenderComponent()
{
    AnimationFrameLength = 2;
    SpriteSheetHeight = 0;
    FrameUpdateTime = 1.0;
    CurrentAnimationTime = 0.0;
    CurrentFrameIndex = 0;
    FrameSize = {64, 64};
}

SpriteSheetRenderComponent::~SpriteSheetRenderComponent()
{
}

SpriteSheetRenderComponent::SpriteSheetRenderComponent(SDL_Renderer *Renderer, SDL_Texture *Texture, SDL_FRect SourceRect)
{
    AnimationFrameLength = 2;
    SpriteSheetHeight = 0;
    FrameUpdateTime = 1.0;
    CurrentAnimationTime = 0.0;
    CurrentFrameIndex = 0;

    this->Renderer = Renderer;
    this->Texture = Texture;
    this->SourceRect = SourceRect;
    this->RenderPosition = SourceRect;

    FrameSize = {SourceRect.w, SourceRect.h};

    this->Texture->w = 1280;
    this->Texture->h = 720;
}

SpriteSheetRenderComponent::SpriteSheetRenderComponent(SDL_Renderer *Renderer, char const *TexturePath, SDL_FRect SourceRect)
{
}

void SpriteSheetRenderComponent::SetRenderer(SDL_Renderer *Renderer)
{
    this->Renderer = Renderer;
}

void SpriteSheetRenderComponent::SetPosition(Vector2D &Position)
{
    RenderPosition.x = Position.x;
    RenderPosition.y = Position.y;
}

Vector2D SpriteSheetRenderComponent::GetPosition()
{
    return {RenderPosition.x, RenderPosition.y};
}

SDL_Texture *SpriteSheetRenderComponent::LoadTexture(char const *path)
{
    SDL_Surface *image_surface = SDL_LoadBMP(path);

    if (!image_surface)
    {
        std::cout << "Failed to load: " << path << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(nullptr, image_surface);

    if (!texture)
    {
        std::cout << "Failed to create texture from .bmp image: " << path << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}

void SpriteSheetRenderComponent::Draw(double DeltaTime)
{
    if (!Renderer || !Texture)
    {
        return;
    }

    CurrentAnimationTime += 25 * DeltaTime;

    if (CurrentAnimationTime >= FrameUpdateTime)
    {
        if (CurrentFrameIndex < AnimationFrameLength)
        {
            SourceRect.x += FrameSize.x;
            CurrentFrameIndex++;
        }
        else if (CurrentAnimationTime >= FrameUpdateTime && CurrentFrameIndex >= AnimationFrameLength)
        {
            SourceRect.x = 0;
            CurrentFrameIndex = 0;
        }
        CurrentAnimationTime = 0;
    }

    SourceRect.y = 0;
    RenderPosition.y = 0;

    SDL_RenderTexture(Renderer, Texture, &SourceRect, &RenderPosition);
}
