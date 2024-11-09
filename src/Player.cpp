#include <algorithm> // For std::find
#include <array>
#include <iostream>

#include "Player.h"
#include "TextureManager.h"

Player::Player(const Map &map, SDL_Texture *cTexture) : Character(map, cTexture)
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
    if (!clickableElements.empty())
    {
        for (int i = 0; i < clickableElements.size(); i++)
        {
            auto [x, y] = map.getScreenPos(clickableElements[i].first, clickableElements[i].second);
            destRect.x = x;
            destRect.y = y;
            TextureManager::DrawTexture(TextureManager::spellRangeTile, srcRect, destRect);
        }
    }
}

void Player::update()
{
    // TODO : Check if player is still alive

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
                previewSpellOne();
                break;
            case SDLK_2:
                previewSpellTwo();
                break;
            case SDLK_3:
                previewSpellThree();
                break;
            case SDLK_ESCAPE:
                std::cout << "Escape key pressed." << std::endl;
                break;
            default:
                // std::cout << "Invalid key pressed." << std::endl;
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
            {
                int x = event.button.x;
                int y = event.button.y;
                // std::cout << "Left mouse button pressed at (" << x << ", " << y << ")" << std::endl;
                auto clickedCell = map.findClickedCell(x, y);
                processClick(clickedCell);
                break;
            }
            default:
                // std::cout << "Invalid mouse button pressed." << std::endl;
                break;
            }
            break;
        }
    }
}

void Player::processClick(std::pair<int, int> pos)
{
    // Check if we click on
    if (std::find(clickableElements.begin(), clickableElements.end(), pos) != clickableElements.end())
    {
        for (size_t i = 0; i < activatedSpells.size(); ++i)
        {
            if (activatedSpells[i])
            {
                switch (i)
                {
                case 0:
                    castSpellOne(pos.first, pos.second);
                    break;
                case 1:
                    castSpellTwo(pos.first, pos.second);
                    break;
                case 2:
                    castSpellThree(pos.first, pos.second);
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }

    // clean spells whether the click was valid or not.
    cleanSpells();
}

void Player::cleanSpells()
{
    // Remove all clickable elements
    clickableElements.clear();

    // Remove any spell selection
    activatedSpells.reset();
}

void Player::addClickableElements(std::vector<std::pair<int, int>> elems)
{
    for (const auto &e : elems)
    {
        if (!map.isOutOfMap(e.first, e.second))
            clickableElements.emplace_back(std::make_pair(e.first, e.second));
    }
}

void Player::previewSpellOne()
{
    std::cout << "Preview spell 1" << std::endl;

    // Clear any previous spell selection
    cleanSpells();

    // Check if we meet the condition to cast the spell

    // Select the first spell
    activatedSpells[0] = 1;

    // Get player position
    int x = getPosX();
    int y = getPosY();

    // Four cells around the player
    std::vector<std::pair<int, int>> pos =
        {
            std::pair<int, int>{x - 1, y},
            std::pair<int, int>{x, y + 1},
            std::pair<int, int>{x + 1, y},
            std::pair<int, int>{x, y - 1}};

    // Add elements to the 'clickableElements' vector
    addClickableElements(pos);
}

void Player::previewSpellTwo()
{

    std::cout << "Preview spell 2" << std::endl;

    // Clear any previous spell selection
    cleanSpells();

    // Check if we meet the condition to cast the spell

    // Select the first spell
    activatedSpells[1] = 1;

    // Get player position
    int x = getPosX();
    int y = getPosY();

    // Height cells around the player
    std::vector<std::pair<int, int>> pos =
        {
            std::pair<int, int>{x - 1, y},
            std::pair<int, int>{x, y + 1},
            std::pair<int, int>{x + 1, y},
            std::pair<int, int>{x, y - 1},
            std::pair<int, int>{x - 2, y},
            std::pair<int, int>{x, y + 2},
            std::pair<int, int>{x + 2, y},
            std::pair<int, int>{x, y - 2},
        };

    // Add elements to the 'clickableElements' vector
    addClickableElements(pos);
}

void Player::previewSpellThree()
{

    std::cout << "Preview spell 3" << std::endl;

    // Clear any previous spell selection
    cleanSpells();

    // Check if we meet the condition to cast the spell

    // Select the first spell
    activatedSpells[2] = 1;

    // Get player position
    int x = getPosX();
    int y = getPosY();

    // Get 4 cells in diagonal
    std::vector<std::pair<int, int>> pos =
        {
            std::pair<int, int>{x - 1, y + 1},
            std::pair<int, int>{x + 1, y + 1},
            std::pair<int, int>{x + 1, y - 1},
            std::pair<int, int>{x - 1, y - 1}};

    // Add elements to the 'clickableElements' vector
    addClickableElements(pos);
}

void Player::castSpellOne(int x, int y)
{
    std::cout << "Casting spell one" << std::endl;

    // Remove one hp
    removeHealtPoint(1);

    // Calculate postion of each elements.

    // For now just update the player position
    setPos(x, y);
}

void Player::castSpellTwo(int x, int y)
{
    std::cout << "Casting spell two" << std::endl;

    // Remove one hp
    removeHealtPoint(2);

    // Calculate postion of each elements.

    // For now just update the player position
    setPos(x, y);
}

void Player::castSpellThree(int x, int y)
{
    std::cout << "Casting spell three" << std::endl;

    // Remove one hp
    removeHealtPoint(3);

    // Calculate postion of each elements.

    // For now just update the player position
    setPos(x, y);
}