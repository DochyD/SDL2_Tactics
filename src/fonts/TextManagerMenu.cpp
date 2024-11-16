#include <stdexcept>
#include <iostream>

#include "TextManagerMenu.h"


TextMenu::TextMenu()
{
    // Load fonts
    LoadFonts();

    // Load texts
    LoadTexts();
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

    
    robotoTitle = TTF_OpenFont("assets/fonts/Roboto-Black.ttf", 48);
    robotoRegular = TTF_OpenFont("assets/fonts/Roboto-Regular.ttf", 32);

    if (robotoTitle == nullptr)
    {
        throw std::runtime_error("Could not load 'robotoTitle' font: " + std::string(TTF_GetError()));
    }

    if (robotoRegular == nullptr)
    {
        throw std::runtime_error("Could not load 'robotoRegular' font: " + std::string(TTF_GetError()));
    }

    // Enable font hinting for better quality
    TTF_SetFontHinting(robotoTitle, TTF_HINTING_LIGHT);
    TTF_SetFontHinting(robotoRegular, TTF_HINTING_LIGHT);
    
    // Enable kerning for better letter spacing
    TTF_SetFontKerning(robotoTitle, 1);
    TTF_SetFontKerning(robotoRegular, 1);
}

// Destroy fonts
void TextMenu::DestroyFonts()
{
    TTF_CloseFont(robotoTitle);
    TTF_CloseFont(robotoRegular);
}

// Loads texts
void TextMenu::LoadTexts()
{
    SDL_Color color = {255, 255, 255, 255};
    TextManager::LoadTextAsTexture(mainTitle, "Main Title", robotoTitle, color);
    TextManager::LoadTextAsTexture(level1Text, "Game 1 : Bolgrot fight from dofus.", robotoRegular, color);
    TextManager::LoadTextAsTexture(level2Text, "Game 2 : Not available", robotoRegular, color);
    TextManager::LoadTextAsTexture(level3Text, "Game 3 : Not Available", robotoRegular, color);
    TextManager::LoadTextAsTexture(settingsText, "Settings (Not Available)", robotoRegular, color);
    TextManager::LoadTextAsTexture(quitGameText, "Quit", robotoRegular, color);

}

// Destroy Texts
void TextMenu::DestroyTexts()
{
    SDL_DestroyTexture(mainTitle);
    SDL_DestroyTexture(level1Text);
    SDL_DestroyTexture(level2Text);
    SDL_DestroyTexture(level3Text);
    SDL_DestroyTexture(settingsText);
    SDL_DestroyTexture(quitGameText);
}

void TextMenu::DrawTitle(int x, int y)
{
    // std::cout << "Draw title" << std::endl;
    // std::cout << mainTitle << std::endl;
    // std::cout << x << std::endl;
    // std::cout << y << std::endl;
    RenderText(mainTitle, x, y);
}

void TextMenu::DrawLevel1Text(int x, int y)
{
    RenderText(level1Text, x, y);
}

void TextMenu::DrawLevel2Text(int x, int y)
{
    RenderText(level2Text, x, y);
}

void TextMenu::DrawLevel3Text(int x, int y)
{
    RenderText(level3Text, x, y);
}

void TextMenu::DrawSetting(int x, int y)
{
    RenderText(settingsText, x, y);
}

void TextMenu::DrawQuit(int x, int y)
{
    RenderText(quitGameText, x, y);
}
