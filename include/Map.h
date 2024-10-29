#pragma once

#include "Game.h"

class Map
{
private:
    int map[10][10];

    const int cellWidth = 60;

    SDL_Rect src, dest;

    SDL_Texture *cellLight;
    SDL_Texture *cellDark;
    SDL_Texture *cellObstacle;

public:
    // Constructor/Destructor
    Map();
    ~Map();

    void loadMap();
    void drawMap();
    void createMap();
};
