#include <string>

#include "TextureManager.h"

namespace TextureManager
{

    SDL_Texture* playerTexture = nullptr;
    SDL_Texture* enemyTexture = nullptr;

    SDL_Texture *LoadTexture(const char *fileName)
    {
        //const std::string fullPath = std::string("assets/sprites/") + fileName;
        SDL_Surface *tmpSurface = IMG_Load(fileName);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);

        return texture;
    }

    void DestroyTexture(SDL_Texture *tex)
    {
        SDL_DestroyTexture(tex);
    } 

    void DestroyTextures()
    {
        SDL_DestroyTexture(playerTexture);
        SDL_DestroyTexture(enemyTexture);
    } 

    void LoadCharacterTexture(const char* fileName)
    {
        playerTexture = LoadTexture(fileName);
    }

    void LoadEnemyTexture(const char* fileName)
    {
        enemyTexture = LoadTexture(fileName);
    }
    
    void DrawTexture(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
    {
        SDL_RenderCopy(Game::renderer, tex, &src, &dest);
    }

}
