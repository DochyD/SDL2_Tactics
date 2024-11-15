// C++ Standard Libraries
#include <iostream>

// Project Specific headers
#include "FontManager.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Game.h"

// Must implement all pure virtual functions
void MenuState::update(Game *game)
{
    // Update menu logic
    // For example: animate menu items
}

void MenuState::render(Game *game)
{
    // Set a black background
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);

    // Render buttons

    // Set text color and font (assuming TTF_Font and SDL_Color are set up)
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    // Render the title
    FontManager::RenderText("MY AWESOME GAME", 100, 50, FontManager::roboto, textColor);


    // Render
    SDL_RenderPresent(Game::renderer);
}

void MenuState::processEvents(Game *game, SDL_Event &event)
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
            std::cout << "key down" << std::endl;
            // Change to play state
            game->setState(new PlayState(1));
            break;
        }
    }
}
