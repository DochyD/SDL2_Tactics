#include <string>
#include <stdexcept>

#include "TextureManager.h"

namespace TextureManager
{
    // Holds the textures we want to load (apart from the on the the grid)
    SDL_Texture *playerTexture = nullptr;
    SDL_Texture *enemyTexture = nullptr;
    SDL_Texture *spellRangeTile = nullptr;

    // Method to load a texture from a path
    SDL_Texture *LoadTexture(const char *fileName)
    {
        // Load surface
        SDL_Surface *tmpSurface = IMG_Load(fileName);
        if (tmpSurface == nullptr)
        {
            std::string errorMsg = "Failed to load texture file: ";
            errorMsg += fileName;
            errorMsg += " - ";
            errorMsg += IMG_GetError();
            throw std::runtime_error(errorMsg);
        }

        // Put surface into texture
        SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        if (texture == nullptr)
        {
            SDL_FreeSurface(tmpSurface);
            std::string errorMsg = "Failed to create texture from surface: ";
            errorMsg += fileName;
            errorMsg += " - ";
            errorMsg += SDL_GetError();
            throw std::runtime_error(errorMsg);
        }

        // Realease surface
        SDL_FreeSurface(tmpSurface);

        return texture;
    }

    // Destroy a texture
    void DestroyTexture(SDL_Texture *tex)
    {
        SDL_DestroyTexture(tex);
    }

    // Load texture for the base map
    void LoadBaseMapTextures()
    {
        playerTexture = LoadTexture("assets/sprites/player.png");
        enemyTexture = LoadTexture("assets/sprites/enemy.png");
        spellRangeTile = LoadTexture("assets/sprites/spellSelectionCell.png");
    }

    // Destroy texture for the base map
    void DestroyBaseMapTextures()
    {
        SDL_DestroyTexture(playerTexture);
        SDL_DestroyTexture(enemyTexture);
        SDL_DestroyTexture(spellRangeTile);
    }

    // Draw texture on screen for a give pos.
    void DrawTexture(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
    {
        SDL_RenderCopy(Game::renderer, tex, &src, &dest);
    }

}
