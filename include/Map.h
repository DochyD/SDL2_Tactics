#pragma once

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include <tuple>

#include "Game.h"
#include "cell.h"

class Map
{
private:
    // Grid
    static const int gridDimension = 33;
    Cell grid[gridDimension][gridDimension];


    // Textures
    // > base texture
    std::tuple<int, int> cellTextureDimension{45, 90};
    SDL_Texture *cellLight = nullptr;
    SDL_Texture *cellDark = nullptr;
    
    // obstacle texture, not used yet
    std::tuple<int, int> obsTextureDimension{45, 90};
    SDL_Texture *cellObstacle = nullptr;

    // Player info
    int playerBaseHealth;
    int playerStartingPosX;
    int playerStartingPosY;

    

public:
    // Constructor/Destructor
    Map();
    ~Map();

    
    // Getters 
    const Cell& getCell(int row, int col) const; // Safe getter for the grid

    int getSize() const { return gridDimension; }
    int getPlayerStartingPosX() const { return playerStartingPosX; }
    int getPlayerStartingPosY() const { return playerStartingPosY; }
    int getPlayerBaseHealth() const { return playerBaseHealth; }

    
    // Safe setter for the grid
    void setCell(int row, int col, const Cell& cell);
    void setCellPosition(int row, int col, float x, float y);
    void setCellType(int row, int col, CellType type);
    void setCellOccupied(int row, int col, bool occupied);

    void setPlayerStartingPosX(int x) { playerStartingPosX = x; }
    void setPlayerStartingPosY(int y) { playerStartingPosY = y; }
    void setPlayerBaseHealth(int h) { playerBaseHealth = h; }
    
    // Methods
    void loadMap(char* filePath);
    void drawMap();
    void createBaseMap(int windowHeight, int windowWidth);

    void findCellPressed(int x, int y);
};