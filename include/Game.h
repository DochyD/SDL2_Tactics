#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game
{
private:
    SDL_Window *window;

    int windowWidth;
    int windowHeight;
    bool windowResized;

    bool isRunning;

public:
    // Static variables
    static SDL_Renderer *renderer;
    static SDL_Event event;

    // Constructor/Destructor
    Game(const char *title, const int width, const int height);
    ~Game();

    bool running() { return isRunning; };
    void processEvents();
    void handleResize(SDL_Event& event);
    void update();
    void render();
};