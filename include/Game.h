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

    // to know if a map is over
    bool levelGameOver = false;
    
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

    bool getGameOver() { return levelGameOver;}
    void setRunning(bool b) { isRunning = b; }

    bool running() { return isRunning; };
    void processEvents();
    void handleResize(SDL_Event &event);
    void update();
    void render();

    void updateEnemies(std::vector<Enemy*>& enemies);

   
};