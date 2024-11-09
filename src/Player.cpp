#include <iostream>

#include "Player.h"
#include "TextureManager.h"

Player::Player(const Map& map, SDL_Texture *cTexture) : Character(map, cTexture)
{
    // Add stuff related to spells I guess ~
}

Player::~Player()
{
}

void Player::draw()
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

    // Draw spell selection if needed

    if(!spellPreview.empty())
    {
        TextureManager::DestroyTexture(TextureManager::spellRangeTile)
    }


}

void Player::update()
{
    // Process event queue
    processEventQueue();
}

void Player::processEventQueue()
{
    while (!eventQueue.empty())
    {
        SDL_Event event = eventQueue.front();
        eventQueue.pop();
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_1:
                spellOne();
                break;
            case SDLK_2:
                std::cout << "Key 2 pressed." << std::endl;
                break;
            case SDLK_3:
                std::cout << "Key 3 pressed." << std::endl;
                break;
            case SDLK_4:
                std::cout << "Key 4 pressed." << std::endl;
                break;
            case SDLK_ESCAPE:
                std::cout << "Escape key pressed." << std::endl;
                break;
            default:
                // std::cout << "Invalid key pressed." << std::endl;
                break;
            }
        }
    }
}

void Player::addEventToQueue(SDL_Event e)
{
    eventQueue.push(e);
}

void Player::spellOne()
{
    std::cout << "Casting spell 1" << std::endl;

    // Find cells we can select (on cell around our character)
    int x = getPosX();
    int y = getPosY();

    std::pair<int, int> pos_1(x - 1, y);
    std::pair<int, int> pos_2(x, y + 1);
    std::pair<int, int> pos_3(x + 1, y);
    std::pair<int, int> pos_4(x, y - 1);


}

void Player::spellTwo()
{
    std::cout << "Casting spell 2" << std::endl;
}

void Player::spellThree()
{
    std::cout << "Casting spell 3" << std::endl;
}
