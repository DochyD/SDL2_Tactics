// C++ Standard Libraries
#include <iostream>
#include <string>
#include <vector>

// Project Specific headers
#include "MenuState.h"
#include "PlayStateOne.h"
#include "Game.h"

// Constructor
MenuState::MenuState() : GameState()
{

    std::string maintTitle = "SDL2 Tactics";
    menuItems = {
        "Level 1 : Bolgrot fight from dofus",
        "Level 2 : Not available",
        "Level 3 : Not available",
        "Settings",
        "Quit game",
    };

    // Select first element in the list
    selectedItem = 0;

    // Set the text manager to a Text Menu object
    textManager = new TextMenu(maintTitle, menuItems);
}

// Destructor
MenuState::~MenuState()
{
    delete textManager;
    textManager = nullptr;
}

// Update menu logic
void MenuState::update()
{
    // Empty for now
    // Usefull if we have animation to handle in our menu
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
            selectedItem = (selectedItem - 1 + menuItems.size()) % menuItems.size();
            break;
        case SDLK_DOWN: // Move selection down
            selectedItem = (selectedItem + 1) % menuItems.size();
            break;
        case SDLK_RETURN: // Select current item

            switch (selectedItem)
            {
            case 0: // Go to playstate 1
                Game::setState(new PlayStateOne());
                break;
            case 1: // Go to playstate 2
                // Game::setState(new PlayState(2));
                std::clog << "Level 2 not implemented yet." << std::endl;
                break;
            case 2: // Go to playstate 3
                // Game::setState(new PlayState(3));
                std::clog << "Level 3 not implemented yet." << std::endl;
                break;
            case 3: // Access settings
                std::clog << "Settings not implemented yet." << std::endl;
                break;
            case 4: // Quit the game
                std::clog << "Quitting game from menu." << std::endl;
                SDL_Event quit_event;
                quit_event.type = SDL_QUIT;
                SDL_PushEvent(&quit_event);
                break;
            }
            break;
        }
    }
}

void MenuState::DrawTitle()
{
    // Calculate center postion
    int x = Game::windowWidth / 2;
    int y = Game::windowHeight / 8;

    // Render the title
    textManager->RenderTitle(x, y);
}

void MenuState::DrawMenuItems()
{
    int x = Game::windowWidth / 10;
    int startY = Game::windowHeight / 4;
    int spacing = 50; // TODO: Make this based in screen height

    bool selected = false;

    for (size_t i = 0; i < menuItems.size(); i++)
    {
        (i == selectedItem) ? selected = true : selected = false;
        textManager->RenderItem(x, startY + i * spacing, i, selected);
    }
}
