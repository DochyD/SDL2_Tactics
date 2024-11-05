#include "Character.h"
#include "TextureManager.h"

Character::Character(int hp, int x, int y, SDL_Texture *cTexture)
{
    healtPoint = hp;

    xPos = x;
    yPos = y;

    xScreen = 0;
    yScreen = 0;

    charTexture = cTexture;
}

Character::~Character()
{
    
}