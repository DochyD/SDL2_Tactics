#pragma once

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include <tuple>

#include "Game.h"
#include "cell.h"

class Map
{
private:
    static const int gridDimension = 33;
    Cell grid[gridDimension][gridDimension];

    SDL_Rect src, dest;

    SDL_Texture *cellLight;
    SDL_Texture *cellDark;
    SDL_Texture *cellObstacle;

    std::tuple<int, int> cellTextureDimension{45, 90};

public:
    // Constructor/Destructor
    Map();
    ~Map();

    // Safe getter for the grid
    const Cell &getCell(int row, int col) const
    {
        if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension)
        {
            return grid[row][col];
        }
        static const Cell invalidCell;
        return invalidCell;
    }

    // Safe setter for the grid
    void setCell(int row, int col, const Cell &cell)
    {
        if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension)
        {
            grid[row][col] = cell;
        }
    }

    // Safe setter for individual cell properties
    void setCellPosition(int row, int col, float x, float y)
    {
        if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension)
        {
            grid[row][col].x = x;
            grid[row][col].y = y;
        }
    }

    void setCellType(int row, int col, CellType type)
    {
        if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension)
        {
            grid[row][col].cellType = type;
        }
    }

    void setCellOccupied(int row, int col, bool occupied)
    {
        if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension)
        {
            grid[row][col].occupied = occupied;
        }
    }

    int getSize() const { return gridDimension; }

    void loadMap(char* filePath);
    void drawMap();
    void createBaseMap(int windowHeight, int windowWidth);
};