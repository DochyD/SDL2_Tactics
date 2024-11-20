#pragma once

// C++ Standard Libraries
#include <vector>

// Third Party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Project Specific headers
//#include "GameState.h"

// Forward declarations
class GameState;
class Map;
class Player;
class Enemy;

class Game
{
private:
    // Window
    SDL_Window *window;
    bool isRunning;

    // Game state
    //static GameState *currentState;

    // Know if level is game over
    bool levelGameOver = false;

    // Map
    static Map *map;

    // Characters
    static Player *player;
    std::vector<Enemy *> enemies;

public:
    // Static variables
    static GameState *currentState;
    static SDL_Renderer *renderer;
    static SDL_Event event;

    static int windowHeight;
    static int windowWidth;

    // Constructor/Destructor
    Game(const char *title, const int width, const int height);
    ~Game();

    // Getters/Setters
    bool getGameOver() { return levelGameOver; }
    void setRunning(bool b) { isRunning = b; }

    // Main methods
    bool running() { return isRunning; };
    void processEvents();
    void handleResize(SDL_Event &event);
    void update();
    void render();

    // Game state methods

    static void setState(GameState* newState);

    // Handle enemies on map
    void updateEnemies(std::vector<Enemy *> &enemies);

};