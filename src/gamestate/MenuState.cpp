// C++ Standard Libraries
#include <iostream>
#include <string>
#include <vector>

// Project Specific headers
#include "MenuState.h"
#include "PlayState.h"
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
    std::cout << "Calling constructor now" << std::endl;
    textManager = new TextMenu(maintTitle, menuItems);
    std::cout << "End of constructor call" << std::endl;
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
    int y = Game::windowHeight / 8;

    // TODO : Make the title at a pos based in window height/width

    // Render the title
    textManager->RenderTitle(x, y);

}

void MenuState::DrawMenuItems()
{
    // // Get menuItems textures
    // const std::vector<SDL_Texture *>& itemTex = textManager.GetItemTextures();
    // const std::vector<SDL_Texture *>& itemSelectedTex = textManager.GetItemTexturesSelected();



    // // TODO : Make menu items at a pos based in window height/width
    // int startY = Game::windowHeight / 4;
    // int spacing = 50;


    // for (size_t i = 0; i < menuItems.size(); i++) {
    //     std::string displayText = (i == selectedItem ? "> " : "  ") + menuItems[i];
        
    //     // Assuming your TextManager has a generic draw text method
    //     SDL_Color color = (i == selectedItem) ? 
    //         SDL_Color{255, 255, 0, 255} :  // Yellow for selected
    //         SDL_Color{255, 255, 255, 255}; // White for unselected
            
    //     //textManager.DrawText(Game::windowWidth / 4, startY + i * spacing, displayText.c_str(), color);
    // }
}
