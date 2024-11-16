#pragma once

// C++ Standard Libraries
#include <string>

// Third Party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Project Specific headers
//#include "Game.h"

class TextManager
{
public:
    // Constructor / Destructor
    TextManager() {}
    ~TextManager() {}

    // Display methods
    void RenderText(SDL_Texture *texture, int x, int y);
    void LoadTextAsTexture(SDL_Texture* &texture, std::string message, TTF_Font* font, SDL_Color color);

    // Basic virtual methods
    virtual void LoadFonts() = 0;
    virtual void DestroyFonts() = 0;
    virtual void LoadTexts() = 0;
    virtual void DestroyTexts() = 0;

};