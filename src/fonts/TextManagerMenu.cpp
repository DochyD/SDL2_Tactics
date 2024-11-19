// Standard library
#include <iostream>
#include <stdexcept>

// Project include
#include "Game.h"
#include "TextManagerMenu.h"

TextMenu::TextMenu(std::string mainTitle, std::vector<std::string> menuItems)
{
    // Load fonts
    LoadFonts();

    // Load texts
    LoadTexts(mainTitle, menuItems);
}

TextMenu::~TextMenu()
{
    // Destroy texts
    DestroyTexts();

    // Destroy fonts
    DestroyFonts();
}

// Load fonts
void TextMenu::LoadFonts()
{

    // TODO make the font size based on the width and height of window...
    mainTitleFont = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 48);
    menuItemFont = TTF_OpenFont("assets/fonts/Roboto-Regular.ttf", 32);

    if (mainTitleFont == nullptr)
    {
        throw std::runtime_error("Could not load 'robotoTitle' font: " + std::string(TTF_GetError()));
    }

    if (menuItemFont == nullptr)
    {
        throw std::runtime_error("Could not load 'robotoRegular' font: " + std::string(TTF_GetError()));
    }

    // Enable font hinting for better quality
    TTF_SetFontHinting(mainTitleFont, TTF_HINTING_LIGHT);
    TTF_SetFontHinting(menuItemFont, TTF_HINTING_LIGHT);

    // Enable kerning for better letter spacing
    TTF_SetFontKerning(mainTitleFont, 1);
    TTF_SetFontKerning(menuItemFont, 1);
}

// Destroy fonts
void TextMenu::DestroyFonts()
{
    TTF_CloseFont(mainTitleFont);
    TTF_CloseFont(menuItemFont);
}

// Loads texts
void TextMenu::LoadTexts(std::string mTitle, std::vector<std::string> menuItems)
{
    SDL_Color whiteColor = {255, 255, 255, 255};
    SDL_Color turquoiseColor = {255, 255, 255, 255};

    LoadTextAsTexture(mainTitleTexture, mTitle, mainTitleFont, whiteColor);

    int w, h;
    if (SDL_QueryTexture(mainTitleTexture, NULL, NULL, &w, &h) != 0)
    {
        std::string error = SDL_GetError();
        mainTitleTexture = nullptr;
        throw std::runtime_error("Texture invalid immediately after creation: " + error);
    }

    for (auto text : menuItems)
    {
        //itemTextures.push_back(TextManager::CreateTextAsTexture("   " + text, menuItemFont, whiteColor));
        //itemSelectedTextures.push_back(TextManager::CreateTextAsTexture(" > " + text, menuItemFont, turquoiseColor));
    }
}

// Destroy Texts
void TextMenu::DestroyTexts()
{
    SDL_DestroyTexture(mainTitleTexture);

    for (size_t i = 0; i < itemTextures.size(); ++i)
    {
        if (itemTextures[i])
        {
            SDL_DestroyTexture(itemTextures[i]);
        }
        if (itemSelectedTextures[i])
        {
            SDL_DestroyTexture(itemSelectedTextures[i]);
        }
    }
    itemTextures.clear(); // Clear both vectors
    itemSelectedTextures.clear();
}

void TextMenu::RenderTitle(int x, int y)
{
    if (!mainTitleTexture)
    {
        std::cerr << "Main title texture is null!" << std::endl;
        return;
    }

    // Get the texture dimensions
    int width, height;
    if (SDL_QueryTexture(mainTitleTexture, NULL, NULL, &width, &height) != 0)
    {
        std::cout << "width :" << width << std::endl;
        std::cout << "height :" << height << std::endl;
        throw std::runtime_error("Failed to query texture's parameters: " + std::string(SDL_GetError()));
    }

    // Create destination rectangle
    SDL_Rect destRect = {
        x - width / 2,  // Center horizontally
        y - height / 2, // Center vertically
        width,
        height};

    // Render the texture
    SDL_RenderCopy(Game::renderer, mainTitleTexture, NULL, &destRect);
}
