#pragma once

// C++ Standard Libraries
#include <string>
#include <vector>

// Project Specific headers
#include "TextManager.h"

class TextLevelOne : public TextManager
{
private:
    // Fonts
    TTF_Font *textFont = nullptr;

    // Colors
    SDL_Color whiteColor = SDL_Color{255, 255, 255, 255};

    SDL_Texture* textTexture;
    SDL_Rect textRect;


public:
    // Constructor / Destructor
    TextLevelOne();
    ~TextLevelOne();

    // Virtual methods
    void LoadFonts() override;
    void DestroyFonts() override;
    void LoadTexts() override {}; // empty as I want to use the method below in that case
    // void LoadTexts(std::string mainTitle, std::vector<std::string> menuItems);
    void DestroyTexts() override;

    // Draw functions
    void RenderTurn(int x, int y, int t);
};