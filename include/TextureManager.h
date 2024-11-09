#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"

namespace TextureManager
{

    extern SDL_Texture* playerTexture;
    extern SDL_Texture* enemyTexture;
    extern SDL_Texture* spellRangeTile;
    

    SDL_Texture* LoadTexture(const char *fileName);
    void DestroyTexture(SDL_Texture* texture);
    
    // Base map texture managment
    void LoadBaseMapTextures();
    void DestroyBaseMapTextures();

    // General method to draw textures
    void DrawTexture(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);

};
