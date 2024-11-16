#pragma once

// Third Party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


// Forward declaration
class TextManager; 
//class Game;

class GameState
{
public:
    GameState() {};
    virtual ~GameState() {};

    virtual void update() = 0;
    virtual void render() = 0;
    virtual void processEvents(SDL_Event &event) = 0;

};