#pragma once

#include <utility> // used for std::pair

#include "Game.h"
#include "cell.h"

class Map
{
private:
    // Grid
    static const int gridDimension = 33;
    Cell grid[gridDimension][gridDimension];

    int numberCellWidth = 15;
    int numberCellHeight = 19;

    int scale = 1;


    // Textures
    // > base texture
    std::pair<int, int> cellTextureDimension{45, 90};
    SDL_Texture *cellLight = nullptr;
    SDL_Texture *cellDark = nullptr;
    
    // obstacle texture, not used yet
    std::pair<int, int> obsTextureDimension{45, 90};
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
    int getPlayerStartingScreenPosX() const { return getCell(playerStartingPosX, playerStartingPosY).x; }
    int getPlayerStartingScreenPosY() const { return getCell(playerStartingPosX, playerStartingPosY).y; }
    int getPlayerBaseHealth() const { return playerBaseHealth; }
    int getNumberCellWidth() const { return numberCellWidth; }
    int getNumberCellHeight() const { return numberCellHeight; }
    std::pair<int, int> getScreenPos(int x, int y) const { return std::make_pair(grid[x][y].x,grid[x][y].y); }

    
    // Safe setter for the grid
    void setCell(int row, int col, const Cell& cell);
    void setCellPosition(int row, int col, float x, float y);
    void setCellType(int row, int col, CellType type);
    void setCellOccupied(int row, int col, bool occupied);

    void setPlayerStartingPosX(int x) { playerStartingPosX = x; }
    void setPlayerStartingPosY(int y) { playerStartingPosY = y; }
    void setPlayerBaseHealth(int h) { playerBaseHealth = h; }

    // Utility
    bool isOutOfMap(int x, int y) { return getCell(x, y).cellType == NO_RENDER; }
    
    // Methods
    void loadMap(char* filePath);
    void drawMap();
    void createBaseMap(int windowHeight, int windowWidth);

    std::pair<int, int> findClickedCell(int x, int y);
};