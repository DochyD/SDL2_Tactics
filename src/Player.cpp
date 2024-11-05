#include <tuple>
#include <iostream>

#include "Player.h"
#include "TextureManager.h"


Player::Player(int hp, int x, int y, SDL_Texture *cTexture) : Character(hp, x, y, cTexture)
{
    // Add stuff related to spells I guess ~

}

Player::~Player()
{

}

void Player::draw() 
{
    SDL_Rect srcRect, destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = std::get<0>(getCharTextureDimension());
    srcRect.w = std::get<1>(getCharTextureDimension());

    // TODO
    // resizing isn't being took care of here (based on the window's size)
    destRect.x = getScreenX();
    destRect.y = getScreenY();
    destRect.h = std::get<0>(getCharTextureDimension());
    destRect.w = std::get<1>(getCharTextureDimension());

    TextureManager::DrawTexture(getCharTexture(), srcRect, destRect);
}

void Player::update() 
{

}