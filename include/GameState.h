#pragma once

// Third Party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


// Forward declaration
class Game; 

class GameState
{
public:
    virtual ~GameState() = default;
    virtual void update(Game *game) = 0;
    virtual void render(Game *game) = 0;
    virtual void processEvents(Game *game, SDL_Event &event) = 0;
};