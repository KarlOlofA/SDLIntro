
#pragma once

#include <SDL3/SDL.h>
#include "../../ObjectComponent\ObjectComponent.hpp"
#include "../../Utils/Types/Vector2D";

class SpriteSheetRenderComponent : ObjectComponent{

public:

    SpriteSheetRenderComponent();
    ~SpriteSheetRenderComponent();

    SpriteSheetRenderComponent(SDL_Renderer* Renderer, SDL_Texture* Texture, SDL_FRect SourceRect);
    SpriteSheetRenderComponent(SDL_Renderer* Renderer, char const *TexturePath, SDL_FRect SourceRect);

    void SetPosition(Vector2D& Position);
    Vector2D GetPosition();

    // Rendering
    void SetRenderer(SDL_Renderer* Renderer);
    SDL_Texture *LoadTexture(char const *Path);

    void Draw(double DeltaTime);

private:

    // How long an animation is in frames.
    int AnimationFrameLength;
    // How what index of the animations that is being shown.
    int CurrentFrameIndex;
    // How many rows of animation the sheet has.
    int SpriteSheetHeight;
    // How long it takes to switch between frames in the animation.
    double FrameUpdateTime;
    // How far along the animation progress the timer has run.
    double CurrentAnimationTime;

    Vector2D FrameSize;

    SDL_Renderer* Renderer;

    SDL_Texture* Texture;
    SDL_FRect SourceRect;
    SDL_FRect RenderPosition;

};