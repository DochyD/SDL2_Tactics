#include <iostream>
#include <stdexcept>

#include "TextManager.h"

#include "Game.h"

// Render Text
void TextManager::RenderText(SDL_Texture* texture, int x, int y)
{
    if (!texture)
    {
        throw std::runtime_error("Attempted to render null texture: ");
        return;
    }

    int width;
    int height;
    std::cout << texture << std::endl;
    if (SDL_QueryTexture(texture, NULL, NULL, &width, &height) != 0)
    {
        throw std::runtime_error("Failed to query texture's parameters: " + std::string(SDL_GetError()));
        return;
    }

    SDL_Rect dstRect = {x, y, width, height};

    // Enable blending for better quality
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    if (SDL_RenderCopy(Game::renderer, texture, nullptr, &dstRect) != 0)
    {
        throw std::runtime_error("Failed to render texture: " + std::string(SDL_GetError()));
    }
}

// Menu related methods
void TextManager::LoadTextAsTexture(SDL_Texture *&texture, std::string message, TTF_Font *font, SDL_Color color)
{
    // First make sure the renderer is valid
    if (!Game::renderer)
    {
        throw std::runtime_error("Renderer is null!");
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, message.c_str(), color);
    if (!surface)
    {
        throw std::runtime_error("Failed to create surface: " + std::string(TTF_GetError()));
    }

    
    // Delete old texture if it exists
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    
    if (!texture)
    {
        SDL_FreeSurface(surface);
        throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
        return;
    }

    int w, h;
    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) != 0)
    {
        std::string error = SDL_GetError();
        SDL_DestroyTexture(texture);
        texture = nullptr;
        throw std::runtime_error("Texture invalid immediately after creation: " + error);
    }

    SDL_FreeSurface(surface);

}

// Create a texture based on text
SDL_Texture *CreateTextAsTexture(std::string message, TTF_Font *font, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Blended(font, message.c_str(), color);
    if (!surface)
    {
        throw std::runtime_error("Failed to create surface: " + std::string(TTF_GetError()));
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    if (!texture)
    {
        throw std::runtime_error("Failed to create texture: " + std::string(TTF_GetError()));
    }
    SDL_FreeSurface(surface);

    return texture;
}
