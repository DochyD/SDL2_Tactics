#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

class Map;
class Player;
class Enemy;

class Game
{
private:
    // Window
    SDL_Window *window;

    bool isRunning;

    // Map
    static Map *map;
    
    // Characters
    static Player *player;
    std::vector<Enemy*> enemies;


public:
    // Static variables
    static SDL_Renderer *renderer;
    static SDL_Event event;

    static int windowHeight;
    static int windowWidth;

    // Constructor/Destructor
    Game(const char *title, const int width, const int height);
    ~Game();

    bool running() { return isRunning; };
    void processEvents();
    void handleResize(SDL_Event &event);
    void update();
    void render();

    void updateEnemies(std::vector<Enemy*>& enemies);
};