#include <iostream>
#include <stdexcept>

#include "TextManager.h"

#include "Game.h"

// Render Text
void TextManager::RenderText(SDL_Texture *texture, int x, int y)
{
    if (!texture) {
        std::cerr << "Attempted to render null texture" << std::endl;
        return;
    }

    int width;  
    int height;
    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        std::cerr << "Failed to query texture: " << SDL_GetError() << std::endl;
        return;
    }
    
    SDL_Rect dstRect = {x, y, width, height};
    
    // Enable blending for better quality
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    
    if (SDL_RenderCopy(Game::renderer, texture, nullptr, &dstRect) != 0) {
        std::cerr << "Failed to render texture: " << SDL_GetError() << std::endl;
    }

}

// Menu related methods
void TextManager::LoadTextAsTexture(SDL_Texture* &texture, std::string message, TTF_Font* font, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Blended(font, message.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to create surface: " << TTF_GetError() << std::endl;
        return;
    }
    
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }
    
    SDL_FreeSurface(surface);
}

