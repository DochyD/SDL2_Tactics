#include "Character.h"
#include "TextureManager.h"

Character::Character(const Map& mMap, SDL_Texture *cTexture) : map(mMap)
{

    // healtPoint = map.getPlayerBaseHealth();

    // xPos = map.getPlayerStartingPosX();
    // yPos = map.getPlayerStartingPosY();

    // xScreen = map.getPlayerStartingScreenPosX();
    // yScreen = map.getPlayerStartingScreenPosY();

    charTexture = cTexture;
}

Character::~Character()
{
    
}

void Character::setPos(int x, int y)
{
    // Update player pos
    
    xPos = x;
    yPos = y;

    // Update palyer screen pos
    auto [xScreen, yScreen] = map.getScreenPos(x, y);
    setScreenPos(xScreen, yScreen);
}