#include <iostream>

// Project includes
#include "Map.h"
#include "TextureManager.h"
#include "Game.h"

// Third party
// #include "json_utils.h"

Map::Map()
{
    cellLight = TextureManager::LoadTexture("assets/sprites/lightCell.png");
    cellDark = TextureManager::LoadTexture("assets/sprites/darkCell.png");
    cellObstacle = TextureManager::LoadTexture("assets/sprites/player.png");
}
Map::~Map()
{
    SDL_DestroyTexture(cellLight);
    SDL_DestroyTexture(cellDark);
    SDL_DestroyTexture(cellObstacle);
}

void Map::loadMap()
{
    // Use json to read the file.
    // Add map to the 'map' object.
}

void Map::drawMap()
{
    // Use json to read the file.
    // Add map to the 'map' object.
}

void Map::createMap(int windowHeight, int windowWidth)
{
    //SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    //SDL_RenderClear(Game::renderer); // Clear the renderer with the draw color

    // Created for  1400 * 1050

    SDL_Rect srcRect;
    SDL_Rect destRect;

    int numberCellWidth = 15;
    int numberCellHeight = 20;

    int scale = 1;
    int baseHeight = 45;
    int baseWidth= 90;



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

    std::cout << "---------" << std::endl;


    int xGrid;
    int yGrid;

    // Draw the grid (Top side)
    for (int line = numberCellWidth; line > 0; --line) {
        int numberOfGridToDraw = ((numberCellWidth - line) * 2) + 1;
        xGrid = numberCellWidth - line;
        std::cout << "--" << std::endl;
        
        
        for (int grid = 0; grid < numberOfGridToDraw; ++grid) {
            destRect.x = (line * (destRect.w - scale * 2)) + (grid * (destRect.w/2 - scale)) - destRect.w + scale * 2 + xOffset;        
            destRect.y = ((destRect.h/2 - scale/2) * grid) + yOffset;

            yGrid = grid + (14 - (numberOfGridToDraw / 2));
            std::cout << xGrid << std::endl;
            std::cout << yGrid << std::endl;
            
            // Add the cell to the IsometricGrad object
            map[xGrid][yGrid].x = destRect.x;
            map[xGrid][yGrid].y = destRect.y;
            map[xGrid][yGrid].cellType = WALKABLE;

            if (grid % 2 == 0) {
                TextureManager::DrawTexture(cellLight, srcRect, destRect);
            } else {
                TextureManager::DrawTexture(cellDark, srcRect, destRect);
            }
        }
    }

    // Draw the grid bottom side.
    for (int line = 1; line < numberCellHeight; ++line) {

        int numberOfGridToDraw;
        
        // Number of grid to draw isn't linear because we have a rectangle shape.
        // We need to compensate because height > width
        // Also the line starting from the corner was drawn by the loop above
        // hence the two "-1" in the following lines 

        if (line <= (numberCellHeight - numberCellWidth)){
            numberOfGridToDraw = ((numberCellWidth - 1) * 2) + 1;
        }
        else{
            numberOfGridToDraw = ((numberCellHeight - line - 1) * 2) + 1;
        }


        //xGrid = line + numberCellWidth - 1;
        xGrid = line + numberCellWidth -1 -1 ;
        std::cout << "--" << std::endl;
        std::cout << xGrid << std::endl;
        for (int grid = 0; grid < numberOfGridToDraw; ++grid) {
            // Calculate isometric coordinates
            destRect.x = ((destRect.w/2 - scale) * grid) + xOffset;
            destRect.y = ((destRect.h - scale) * line) + ((destRect.h/2 - scale / 2) * grid) + yOffset;
            
            yGrid = line + grid;

            map[xGrid][yGrid].x = destRect.x;
            map[xGrid][yGrid].y = destRect.y;
            map[xGrid][yGrid].cellType = WALKABLE;

            // Alternate colors
            if (grid % 2 == 0) {
                TextureManager::DrawTexture(cellLight, srcRect, destRect);
            } else {
                TextureManager::DrawTexture(cellDark, srcRect, destRect);
            }
        }
    }

}
