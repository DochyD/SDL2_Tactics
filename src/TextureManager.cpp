#include "TextureManager.h"

namespace TextureManager
{

    SDL_Texture *LoadTexture(const char *fileName)
    {
        
        SDL_Surface *tmpSurface = IMG_Load(fileName);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);

        return texture;
    }

    void DestroyTexture(SDL_Texture *tex)
    {
        SDL_DestroyTexture(tex);
    } 
    
    void DrawTexture(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
    {
        SDL_RenderCopy(Game::renderer, tex, &src, &dest);
    }

}
