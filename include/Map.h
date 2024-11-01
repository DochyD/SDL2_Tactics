#pragma once

#include "Game.h"
#include "grid_cell.h"

class Map
{
private:
    GridCell map[33][33];

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
    void createMap(int windowHeight, int windowWidth);
};
