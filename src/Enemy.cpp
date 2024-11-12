#include <algorithm> // For std::find
#include <array>
#include <cmath>
#include <iostream>

#include "Enemy.h"
#include "TextureManager.h"

Enemy::Enemy(const Map &map, SDL_Texture *cTexture) : Character(map, cTexture)
{
    // Set heealt point
    setHealthPoint(1);

    // Set starting position
    setPos(18, 18);
}

Enemy::Enemy(const Map &map, SDL_Texture *cTexture, int x, int y) : Character(map, cTexture)
{
    // Set heealt point
    setHealthPoint(1);

    // Set starting position
    setPos(x, y);
}

Enemy::~Enemy()
{
}

void Enemy::draw()
{
    // Draw player
    SDL_Rect srcRect, destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = getCharTextureDimension().first;
    srcRect.w = getCharTextureDimension().second;

    // TODO
    // resizing isn't being took care of here (based on the window's size)
    destRect.x = getScreenX();
    destRect.y = getScreenY();
    destRect.h = getCharTextureDimension().first;
    destRect.w = getCharTextureDimension().second;

    TextureManager::DrawTexture(getCharTexture(), srcRect, destRect);
}

void Enemy::update()
{
    // empty
}

void Enemy::update(int playerX, int playerY)
{
    int x = getPosX();
    int y = getPosY();
    // Find which direction the enemy needs to do!
    std::cout << "-----" << std::endl;
    std::cout << "x : " << x << std::endl;
    std::cout << "y : " << y << std::endl;

    int diffX = abs(playerX - x);
    int diffY = abs(playerY - y);

    int dirX = (playerX > x) ? 1 : (playerX < x) ? -1 : 0;
    int dirY = (playerY > y) ? 1 : (playerY < y) ? -1 : 0;

    if (diffX == diffY)
    {
        setPos(x + dirX, y + dirY); // Move diagonally
    }
    else if (diffX > diffY)
    {
        setPosX(x + dirX); // Move horizontally
    }
    else
    {
        setPosY(y + dirY); // Move vertically
    }

    
    std::cout << "x : " << getPosX() << std::endl;
    std::cout << "y : " << getPosY() << std::endl;
    
    std::cout << "diffX : " << diffX << std::endl;
    std::cout << "diffY : " << diffY << std::endl;

    std::cout << "dirX : " << dirX << std::endl;
    std::cout << "dirY : " << dirY << std::endl;




    // Check if new position is equal to player postion -> game over
    if (getPosX() == playerX && getPosY() == playerY)
    {
        std::cout << "Game over" << std::endl;
    }
}
