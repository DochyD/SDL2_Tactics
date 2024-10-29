#include <iostream>

// Project includes
#include "Map.h"
#include "TextureManager.h"

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

void Map::createMap()
{
    //SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    //SDL_RenderClear(Game::renderer); // Clear the renderer with the draw color

    SDL_Rect srcRect;
    SDL_Rect destRect;

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


    for(int i = 0; i < 14; i++){
        
        destRect.x = (i * destRect.w) - (i * scale * 2);
        TextureManager::DrawTexture(cellLight, srcRect, destRect);
    }

    for(int i = 0; i < 14; i++){
        
        destRect.x = (i * destRect.w) - (i * scale * 2) + destRect.w / 2 - scale;        
        destRect.y = destRect.h / 2 - scale / 2;
        TextureManager::DrawTexture(cellDark, srcRect, destRect);
    }

    for(int i = 1; i < 20; i++){
        
        destRect.x = 0;        
        destRect.y = (i) * destRect.h - scale;
        TextureManager::DrawTexture(cellLight, srcRect, destRect);
    }




    // // 3rd row

    // for(int i = 0; i <= 14; i++){
        
    //     destRect.x = (i * destRect.w) - (i * scale * 2);

    //     destRect.y = (1) * destRect.h - scale;

    //     TextureManager::DrawTexture(cellLight, srcRect, destRect);
    // }


}
