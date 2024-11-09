#include "Character.h"
#include "TextureManager.h"

Character::Character(const Map& mMap, SDL_Texture *cTexture) : map(mMap)
{

    healtPoint = map.getPlayerBaseHealth();

    xPos = map.getPlayerStartingPosX();
    yPos = map.getPlayerStartingPosY();

    xScreen = map.getPlayerStartingScreenPosX();
    yScreen = map.getPlayerStartingScreenPosY();

    charTexture = cTexture;
}

Character::~Character()
{
    
}