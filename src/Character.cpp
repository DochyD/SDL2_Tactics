#include "Character.h"
#include "TextureManager.h"

Character::Character(int x, int y, const char *texPath)
{
    healtPoint = 40;

    xPos = x;
    yPos = y;

    charTexture = TextureManager::LoadTexture(texPath);
}

Character::~Character()
{
    TextureManager::DestroyTexture(charTexture);
}