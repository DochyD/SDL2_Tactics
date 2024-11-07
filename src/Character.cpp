#include "Character.h"
#include "TextureManager.h"

Character::Character(int hp, int x, int y, int screenX, int screenY, SDL_Texture *cTexture)
{
    healtPoint = hp;

    xPos = x;
    yPos = y;

    xScreen = screenX;
    yScreen = screenY;

    charTexture = cTexture;
}

Character::~Character()
{
    
}