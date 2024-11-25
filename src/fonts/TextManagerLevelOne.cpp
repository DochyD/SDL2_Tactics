// Standard library
#include <iostream>
#include <stdexcept>

// Project include
#include "Game.h"
#include "TextManagerLevelOne.h"

TextLevelOne::TextLevelOne()
{
    // Load fonts
    LoadFonts();

    // Load texts
    LoadTexts();
}

TextLevelOne::~TextLevelOne()
{
    // Destroy texts
    DestroyTexts();

    // Destroy fonts
    DestroyFonts();
}

// Load fonts
void TextLevelOne::LoadFonts()
{
    // TODO make the font size based on the width and height of window...
    textFont = TTF_OpenFont("assets/fonts/Roboto-Regular.ttf", 32);

    if (textFont == nullptr)
    {
        throw std::runtime_error("Could not load 'robotoRegular' font: " + std::string(TTF_GetError()));
    }

    // Enable font hinting for better quality
    TTF_SetFontHinting(textFont, TTF_HINTING_LIGHT);

    // Enable kerning for better letter spacing
    // TTF_SetFontKerning(mainTitleFont, 1);
    // TTF_SetFontKerning(menuItemFont, 1);
}

// Destroy fonts
void TextLevelOne::DestroyFonts()
{
    TTF_CloseFont(textFont);
}

void TextLevelOne::DestroyTexts()
{
    SDL_DestroyTexture(textTexture);
    textTexture = nullptr;
}

void TextLevelOne::RenderTurn(int x, int y, int t)
{
    // Create text string
    std::string turnText = "Turn: " + std::to_string(t);

    // Render text surface
    SDL_Surface *textSurface = TTF_RenderText_Blended(textFont, turnText.c_str(), whiteColor);
    if (textSurface == nullptr)
    {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Create texture from surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
    if (textTexture == nullptr)
    {
        SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Set rendering dimensions
    textRect.x = x;
    textRect.y = y;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;



    // Render the text texture
    SDL_RenderCopy(Game::renderer, textTexture, nullptr, &textRect);

    // Free the surface as it's no longer needed
    SDL_FreeSurface(textSurface);
}


void TextLevelOne::RenderHealthPoint(int x, int y, int hp)
{
    // Create text string
    std::string turnText = "Player's hp: " + std::to_string(hp);

    // Render text surface
    SDL_Surface *textSurface = TTF_RenderText_Blended(textFont, turnText.c_str(), whiteColor);
    if (textSurface == nullptr)
    {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Create texture from surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
    if (textTexture == nullptr)
    {
        SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Set rendering dimensions
    textRect.x = x;
    textRect.y = y;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;



    // Render the text texture
    SDL_RenderCopy(Game::renderer, textTexture, nullptr, &textRect);

    // Free the surface as it's no longer needed
    SDL_FreeSurface(textSurface);
}

void TextLevelOne::RenderActionPoint(int x, int y, int ap)
{
    // Create text string
    std::string turnText = "Player's ap: " + std::to_string(ap);

    // Render text surface
    SDL_Surface *textSurface = TTF_RenderText_Blended(textFont, turnText.c_str(), whiteColor);
    if (textSurface == nullptr)
    {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Create texture from surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
    if (textTexture == nullptr)
    {
        SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Set rendering dimensions
    textRect.x = x;
    textRect.y = y;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;



    // Render the text texture
    SDL_RenderCopy(Game::renderer, textTexture, nullptr, &textRect);

    // Free the surface as it's no longer needed
    SDL_FreeSurface(textSurface);
}