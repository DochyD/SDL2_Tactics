// C++ Standard Libraries
#include <iostream>

// Project Specific headers
#include "MenuState.h"
#include "PlayState.h"
#include "Game.h"


// Constructor
MenuState::MenuState() : GameState()
{

    menuItems = {
        "Level 1 : Bolgrot fight from dofus",
        "Level 2",
        "level 3",
        "Settings",
        "Quit game",
    };

    // Select first element in the list
    selectedItem = 0;

    // Set the text manager to a Text Menu object
    
}

// Destructor
MenuState::~MenuState()
{
    // Destroy TextManager
    // DestroyTextManager();
}


// Update menu logic
void MenuState::update()
{
    // Update menu logic
    // For example: animate menu items
}

// Render menu logic
void MenuState::render()
{
    // Set a black background
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);

    // Draw main title
    DrawTitle();
    
    // Draw menu items
    DrawMenuItems();

    // Render
    SDL_RenderPresent(Game::renderer);
}

// Process menu events
void MenuState::processEvents(SDL_Event &event)
{
    // Handle menu input
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP: // Move selection up
            std::cout << "key up" << std::endl;
            break;
        case SDLK_DOWN: // Move selection down
            std::cout << "key down" << std::endl;
            break;
        case SDLK_RETURN: // Select current item
            std::cout << "Go to playstate ~" << std::endl;
            // Change to play state
            Game::setState(new PlayState(1));
            break;
        }
    }
}


void MenuState::DrawTitle()
{
    SDL_Color textColor = {255, 255, 255, 255}; // White color


    // Calculate center postion
    int x = Game::windowWidth / 2;

    // Render the title
    textManager.DrawTitle(100, 100);

}

void MenuState::DrawMenuItems()
{
    textManager.DrawLevel1Text(100, 200);
    textManager.DrawLevel2Text(100, 250);
    textManager.DrawLevel3Text(100, 300);
    
    textManager.DrawSetting(100, 400);
    textManager.DrawQuit(100, 450);
}
