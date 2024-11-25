#pragma once

#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Map.h"

class Character
{
private:
    int healtPoint;

    int xPos, yPos;
    int xScreen, yScreen;

    SDL_Texture *charTexture;
    std::pair<int, int> charTextureDimension{45, 90};

protected:
    // Ref to the map.
    // We want the derivated class to access it.
    const Map& map;

public:
    // Constructor / Destructor
    Character(const Map& map, SDL_Texture *cTexture);
    ~Character();

    // Getters
    int getHealthPoint() { return healtPoint; }
    std::pair<int, int> getPos() { return std::make_pair(xPos, yPos); }
    int getPosX() { return xPos; }
    int getPosY() { return yPos; }
    int getScreenX() { return xScreen; }
    int getScreenY() { return yScreen; }

    // Setters
    void setHealthPoint(int hp) { healtPoint = hp; }
    void setPos(int x, int y);
    void setPosX(int x) { setPos(x, yPos); }
    void setPosY(int y) { setPos(xPos, y); }
    void setScreenPos(int x, int y) { xScreen = x; yScreen = y; }
    void removeHealtPoint(int hp) { healtPoint -= hp ; }

    // Texture 
    SDL_Texture *getCharTexture() { return charTexture; }
    std::pair<int, int> &getCharTextureDimension() { return charTextureDimension; }

    // Basic methods
    virtual void draw() = 0;
    virtual void update() = 0;
};