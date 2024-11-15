#pragma once

// C++ Standard Libraries
#include <string>

// Third Party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Project Specific headers
#include "Game.h"

namespace FontManager
{

    // 'extern' keyword so that roboto font here is only a declaration
    extern TTF_Font* roboto;

    void InitFonts();
    void DestroyFonts();
    void RenderText(const std::string &message, int x, int y, TTF_Font *font, SDL_Color color);

}