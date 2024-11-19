#include <iostream>

#include "MenuState.h"
#include "PlayState.h"

#include "Game.h"

PlayState::PlayState(int level)
{
    currentLevel = level;

    // TODO make everything based on level!

    // Load textures

    // Load fonts

    // Load text textures
}

PlayState::~PlayState()
{
}

void PlayState::update()
{
    // Update menu logic
    // For example: animate menu items
}

void PlayState::render()
{
    // Set a black background
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    SDL_RenderClear(Game::renderer);

    // Render
    SDL_RenderPresent(Game::renderer);
}

void PlayState::processEvents(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            Game::setState(new MenuState());
        }
        // ... your existing game controls ...
    }
}