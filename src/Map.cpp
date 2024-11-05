#include <iostream>

// Project includes
#include "Map.h"
#include "TextureManager.h"
// #include "Game.h"

// Third party
#include "json_utils.h"

Map::Map()
{
    cellLight = TextureManager::LoadTexture("assets/sprites/lightCell.png");
    cellDark = TextureManager::LoadTexture("assets/sprites/darkCell.png");
    // cellObstacle = TextureManager::LoadTexture("assets/sprites/player.png");
}
Map::~Map()
{
    TextureManager::DestroyTexture(cellLight);
    TextureManager::DestroyTexture(cellDark);
    // TextureManager::DestroyTexture(cellObstacle);
}


const Cell& Map::getCell(int row, int col) const {
    if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension) {
        return grid[row][col];
    }
    static const Cell invalidCell;
    return invalidCell;
}

void Map::setCell(int row, int col, const Cell& cell) {
    if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension) {
        grid[row][col] = cell;
    }
}

void Map::setCellPosition(int row, int col, float x, float y) {
    if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension) {
        grid[row][col].x = x;
        grid[row][col].y = y;
    }
}

void Map::setCellType(int row, int col, CellType type) {
    if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension) {
        grid[row][col].cellType = type;
    }
}

void Map::setCellOccupied(int row, int col, bool occupied) {
    if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension) {
        grid[row][col].occupied = occupied;
    }
}


// Load map from json
void Map::loadMap(char *filePath)
{
    if (JsonUtils::loadGridFromJson(*this, filePath))
    {
        std::clog << "Map '" << filePath << "' loaded successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Failed to load map" << std::endl;
    }
}

// Draw the map based on info from the map object
void Map::drawMap()
{
    SDL_Rect srcRect, destRect;

    // TODO
    // ideally this info would be queried from the map object (and stored in the map json)
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = std::get<0>(cellTextureDimension);
    srcRect.w = std::get<1>(cellTextureDimension);

    // TODO
    // resizing isn't being took care of here (based on the window's size)
    destRect.h = std::get<0>(cellTextureDimension);
    destRect.w = std::get<1>(cellTextureDimension);

    for (int row = 0; row < gridDimension; row++)
    {
        for (int col = 0; col < gridDimension; col++)
        {
            const Cell &cell = getCell(row, col);

            if (cell.cellType != NO_RENDER)
            {
                if (row < 33)
                {
                    destRect.x = cell.x;
                    destRect.y = cell.y;

                    if ((col + row) % 2 == 0)
                    {
                        TextureManager::DrawTexture(cellLight, srcRect, destRect);
                    }
                    else
                    {
                        TextureManager::DrawTexture(cellDark, srcRect, destRect);
                    }
                }
            }
        }
    }
}

// Create the base map and saves it to "base_map.json"
void Map::createBaseMap(int windowHeight, int windowWidth)
{
    // This function is used as a map editor and creates the base map
    // ~ Not fancy but can be used as a base to create other maps.
    // Grid created for window size of 1400 * 1050

    // Reset the grid object in Map class in case we create the map
    // but forgot to remove the map loading.
    Cell baseCell;

    for (int i = 0; i < gridDimension; ++i)
    {
        for (int j = 0; j < gridDimension; ++j)
        {
            grid[i][j] = baseCell; // Set each cell to the base value
        }
    }

    // Variables used to create the grid
    SDL_Rect srcRect;
    SDL_Rect destRect;

    int numberCellWidth = 15;
    int numberCellHeight = 19;

    int scale = 1;
    int baseHeight = 45;
    int baseWidth = 90;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = baseHeight;
    srcRect.w = baseWidth;

    destRect.x = 0;
    destRect.y = 0;
    destRect.h = baseHeight * scale;
    destRect.w = baseWidth * scale;

    int xOffset = (windowWidth - ((destRect.w - scale * 2) * numberCellWidth)) / 2;
    int yOffset = (windowHeight - ((destRect.h - scale) * numberCellHeight)) / 2;

    int xGrid;
    int yGrid;

    // Draw the grid (Top side)
    for (int line = numberCellWidth; line > 0; --line)
    {
        int numberOfGridToDraw = ((numberCellWidth - line) * 2) + 1;
        xGrid = numberCellWidth - line;

        for (int grid = 0; grid < numberOfGridToDraw; ++grid)
        {
            destRect.x = (line * (destRect.w - scale * 2)) + (grid * (destRect.w / 2 - scale)) - destRect.w + scale * 2 + xOffset;
            destRect.y = ((destRect.h / 2 - scale / 2) * grid) + yOffset;

            //
            yGrid = grid + (14 - (numberOfGridToDraw / 2));

            // Add the cell to the IsometricGrad object
            Cell newCell(destRect.x, destRect.y, WALKABLE, false);
            setCell(xGrid, yGrid, newCell);

            if (grid % 2 == 0)
            {
                TextureManager::DrawTexture(cellLight, srcRect, destRect);
            }
            else
            {
                TextureManager::DrawTexture(cellDark, srcRect, destRect);
            }
        }
    }

    // Draw the grid bottom side.
    for (int line = 1; line < numberCellHeight; ++line)
    {

        int numberOfGridToDraw;

        // Number of grid to draw isn't linear because we have a rectangle shape.
        // We need to compensate because height > width
        // Also the line starting from the corner was drawn by the loop above
        // hence the two "-1" in the following lines

        if (line <= (numberCellHeight - numberCellWidth))
        {
            numberOfGridToDraw = ((numberCellWidth - 1) * 2) + 1;
        }
        else
        {
            numberOfGridToDraw = ((numberCellHeight - line - 1) * 2) + 1;
        }

        xGrid = line + numberCellWidth - 1;
        for (int grid = 0; grid < numberOfGridToDraw; ++grid)
        {
            // Calculate isometric coordinates
            destRect.x = ((destRect.w / 2 - scale) * grid) + xOffset;
            destRect.y = ((destRect.h - scale) * line) + ((destRect.h / 2 - scale / 2) * grid) + yOffset;

            yGrid = line + grid;

            Cell newCell(destRect.x, destRect.y, WALKABLE, false);
            setCell(xGrid, yGrid, newCell);

            // Alternate colors
            if (grid % 2 == 0)
            {
                TextureManager::DrawTexture(cellLight, srcRect, destRect);
            }
            else
            {
                TextureManager::DrawTexture(cellDark, srcRect, destRect);
            }
        }
    }

    // Stuff that is not related to drawing the grid
    this->setPlayerStartingPosX(14);
    this->setPlayerStartingPosY(14);
    this->setPlayerBaseHealth(40);


    // To save the grid:
    if (JsonUtils::saveGridToJson(*this, "base_map.json"))
    {
        std::clog << "Grid saved successfully!" << std::endl;
    }
}

// Find which cell wat clicked on given two coordinates.

void Map::findCellPressed(int x, int y)
{
    
}