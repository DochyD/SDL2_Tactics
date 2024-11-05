#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"

namespace TextureManager
{

    extern SDL_Texture* playerTexture;
    extern SDL_Texture* enemyTexture;

    SDL_Texture* LoadTexture(const char *fileName);
    void DestroyTexture(SDL_Texture* texture);
    void DestroyTextures();

    void LoadCharacterTexture(const char* fileName);
    void LoadEnemyTexture(const char* fileName);

    //extern SDL_Texture* getPlayerTexture() { return playerTexture; }



    void DrawTexture(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest);

};
