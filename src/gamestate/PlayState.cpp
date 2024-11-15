#include "MenuState.h"
#include "PlayState.h"

#include "Game.h"

void PlayState::update(Game *game)
{
    // Update menu logic
    // For example: animate menu items
}

void PlayState::render(Game *game)
{
    // Set a black background
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    SDL_RenderClear(Game::renderer);


    // Render
    SDL_RenderPresent(Game::renderer);
}

void PlayState::processEvents(Game* game, SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            game->setState(new MenuState());
        }
        // ... your existing game controls ...
    }
}