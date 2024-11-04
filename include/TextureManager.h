#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"

namespace TextureManager
{

    SDL_Texture* LoadTexture(const char *fileName);
    void DestroyTexture(SDL_Texture* texture);

    void DrawTexture(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);

};
