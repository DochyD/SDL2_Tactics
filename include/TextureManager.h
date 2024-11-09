#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"

namespace TextureManager
{
    // Character related textures
    extern SDL_Texture *playerTexture;
    extern SDL_Texture *enemyTexture;
    extern SDL_Texture *spellRangeTile;

    // Base map texture managment
    void LoadBaseMapTextures();
    void DestroyBaseMapTextures();

    // General method to work with textures
    SDL_Texture *LoadTexture(const char *fileName);
    void DrawTexture(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);
    void DestroyTexture(SDL_Texture *texture);

};
