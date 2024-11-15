#include <iostream>
#include <stdexcept>

#include "FontManager.h"

namespace FontManager
{
    // Fonts we want to load
    TTF_Font *roboto = nullptr;

    void InitFonts()
    {
        roboto = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 24);
        if (roboto == nullptr)
        {
            throw std::runtime_error("Could not load 'roboto' font");
        }
    }

    void DestroyFonts()
    {
        TTF_CloseFont(roboto);

        // Quit SDL's TTF subsystem
        TTF_Quit();
    }

    void RenderText(const std::string &message, int x, int y, TTF_Font *font, SDL_Color color)
    {
        std::cout << "This is where the game crashes" << std::endl;
        SDL_Surface *surface = TTF_RenderText_Solid(font, message.c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

        SDL_Rect dstRect = {x, y, surface->w, surface->h};
        SDL_RenderCopy(Game::renderer, texture, nullptr, &dstRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }

}
