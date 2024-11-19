#pragma once

// C++ Standard Libraries
#include <string>
#include <vector>

// Project Specific headers
#include "TextManager.h"

class TextMenu : public TextManager
{
private:
    // Fonts
    TTF_Font *mainTitleFont = nullptr;
    TTF_Font *menuItemFont = nullptr;

    // Colors
    SDL_Color whiteColor = SDL_Color{255, 255, 255, 255};
    SDL_Color turquoiseColor = SDL_Color{255, 255, 255, 255};

    std::vector<std::string> menuItems;

    SDL_Texture *mainTitleTexture = nullptr;
    std::vector<SDL_Texture *> itemTextures;
    std::vector<SDL_Texture *> itemSelectedTextures;

public:
    // Constructor / Destructor
    TextMenu() {};
    TextMenu(std::string mainTitle, std::vector<std::string> menuItems);
    ~TextMenu();

    // Virtual methods
    void LoadFonts() override;
    void DestroyFonts() override;
    void LoadTexts() override {}; // empty as I want to use the method below in that case
    void LoadTexts(std::string mainTitle, std::vector<std::string> menuItems);
    void DestroyTexts() override;

    // Draw functions
    void RenderTitle(int x, int y);
    void RenderItem(int x, int y, int index, bool selected);
};