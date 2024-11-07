#include <bitset>
#include <cmath>
#include <iostream>
#include <utility>

// Project includes
#include "Map.h"
#include "TextureManager.h"

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

const Cell &Map::getCell(int row, int col) const
{
    if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension)
    {
        return grid[row][col];
    }
    static const Cell invalidCell;
    return invalidCell;
}

void Map::setCell(int row, int col, const Cell &cell)
{
    if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension)
    {
        grid[row][col] = cell;
    }
}

void Map::setCellPosition(int row, int col, float x, float y)
{
    if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension)
    {
        grid[row][col].x = x;
        grid[row][col].y = y;
    }
}

void Map::setCellType(int row, int col, CellType type)
{
    if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension)
    {
        grid[row][col].cellType = type;
    }
}

void Map::setCellOccupied(int row, int col, bool occupied)
{
    if (row >= 0 && row < gridDimension && col >= 0 && col < gridDimension)
    {
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
    srcRect.h = cellTextureDimension.first;
    srcRect.w = cellTextureDimension.second;

    // TODO
    // resizing isn't being took care of here (based on the window's size)
    destRect.h = cellTextureDimension.first;
    destRect.w = cellTextureDimension.second;

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
    srcRect.h = cellTextureDimension.first;
    srcRect.w = cellTextureDimension.second;

    destRect.x = 0;
    destRect.y = 0;
    destRect.h = cellTextureDimension.first * scale;
    destRect.w = cellTextureDimension.second * scale;

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
    this->setPlayerStartingPosX(16);
    this->setPlayerStartingPosY(16);
    this->setPlayerBaseHealth(40);

    // To save the grid:
    if (JsonUtils::saveGridToJson(*this, "base_map.json"))
    {
        std::clog << "Grid saved successfully!" << std::endl;
    }
}

// Find which cell wat clicked on given two coordinates.

std::pair<int, int> Map::findClickedCell(int x, int y)
{

    // Calculate offsets
    int xOffset = (Game::windowWidth - ((cellTextureDimension.second * scale - scale * 2) * numberCellWidth)) / 2;
    int yOffset = (Game::windowHeight - ((cellTextureDimension.first * scale - scale) * numberCellHeight)) / 2;

    // Early return if click is outside the grid area
    if (x < xOffset || x >= (Game::windowWidth - xOffset) ||
        y < yOffset || y >= (Game::windowHeight - yOffset))
    {
        // std::cout << "Click outside grid bounds" << std::endl;
        return std::make_pair(-99, -99);
    }

    // Get the info of the center of the grid
    int i = getSize() / 2, j = getSize() / 2;
    int xCell = getCell(i, j).x;
    int yCell = getCell(i, j).y;

    // The goal here is to find which cell we click on from the center. we either go up/down and/or right/left
    int directionX = (x < xCell) ? 1 : -1;
    while ((directionX == 1 && x <= xCell) || (directionX == -1 && x >= xCell && x > (xCell + cellTextureDimension.second)))
    {
        i += directionX;
        j -= directionX;
        xCell = getCell(i, j).x;
    }

    // Determine the direction for the y movement
    int directionY = (y < yCell) ? -1 : 1;
    while ((directionY == -1 && y <= yCell) || (directionY == 1 && y >= yCell && y > (yCell + cellTextureDimension.first)))
    {
        i += directionY;
        j += directionY;
        yCell = getCell(i, j).y;
    }

    // At this point we have an approximation of the cell we want to use (as sprites are superposed on top of each other it can be tricky).
    // But the valid postion can only be the one we have, or be on cell away.

    // Top corner pos to get the 4 points of out diamond shape inside the sprite
    int topCornerX = getCell(i, j).x, topCornerY = getCell(i, j).y;

    std::pair<int, int> topPoint{topCornerX + cellTextureDimension.second / 2, topCornerY};
    std::pair<int, int> rightPoint{topCornerX + cellTextureDimension.second, topCornerY + cellTextureDimension.first / 2};
    std::pair<int, int> bottomPoint{topCornerX + cellTextureDimension.second / 2, topCornerY + cellTextureDimension.first};
    std::pair<int, int> leftPoint{topCornerX, topCornerY + cellTextureDimension.first / 2};

    std::array<std::pair<int, int>, 5> points = {
        topPoint,
        rightPoint,
        bottomPoint,
        leftPoint,
        topPoint};

    // Calculate the line formula of each side of the diamong (ax + b)
    
    // Nested function to calculate slope
    auto calculateSlope = [](const std::pair<int, int> &p1, const std::pair<int, int> &p2)
    {
        return static_cast<double>(p2.second - p1.second) / (p2.first - p1.first);
    };

    // Nested function to calculate intercept
    auto calculateIntercept = [](const std::pair<int, int> &point, double slope)
    {
        return static_cast<double>(point.second) - (slope * point.first);
    };

    // We use this bit check to see if we want our point to be above or below a line
    std::bitset<4> bits("1001");

    for (int p = 0; p < 4; p++)
    {
        double a = calculateSlope(points[p], points[p + 1]);
        double b = calculateIntercept(points[p], a);

        double lineY = a * x + b;

        // Based on where our point is, we change the cell we return
        if (y < lineY == bits[p])
        {
            switch (p)
            {
            case 0:
                i--;
                break;
            case 1:
                j++;
                break;
            case 2:
                i++;
                break;
            case 3:
                j--;
                break;
            default:
                break;
            }
            // To make sure we are not clicking outside our visible grid
            if (isOutOfMap(i, j))
            {
                return std::make_pair(-99, -99); // invalid value
            }
        }
    }
    return std::make_pair(i, j);
}