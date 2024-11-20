// C++ Standard Libraries
#include <iostream>
#include <set>

// Project Specific headers
#include "MenuState.h"
#include "PlayStateOne.h"
#include "Game.h"
#include "TextureManager.h"

PlayStateOne::PlayStateOne()
{
    // Set up game variable
    turns = 10;
    timer = 0;
    gameOver = false;

    // Load map
    map = new Map();
    map->loadMap("base_map.json"); // handle texture loading

    // Load textures
    TextureManager::LoadBaseMapTextures();

    // Load player
    player = new Player(*map, TextureManager::playerTexture);

    // Load enemies ?? not sure that needed!

    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 16, 25));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 20, 16));

    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 16));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 17));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 14, 18));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 13, 19));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 12, 20));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 11, 21));

    enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 16));
    enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 14));
    enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 15));
    enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 17));
    enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 18));
}

PlayStateOne::~PlayStateOne()
{
    // Destroy textures
    TextureManager::DestroyBaseMapTextures();

    delete player;
    delete map;

    player = nullptr;
    map = nullptr;

    // TODO : handle enemies
    // delete enemies;
    for (Enemy *enemy : enemies)
    {
        delete enemy; // Free the dynamically allocated memory
    }
    enemies.clear(); // Clear the vector itself
}

void PlayStateOne::update()
{

    // To check if the player's postion got updated
    int xPlayerOld = player->getPosX();
    int yPlayerOld = player->getPosY();

    player->update();

    int xPlayer = player->getPosX();
    int yPlayer = player->getPosY();

    // If the player pos got updated, then we need to update the enemies.
    if (xPlayerOld != xPlayer || yPlayerOld != yPlayer)
    {
        updateEnemies(enemies);
    }

    // Check if enemy pos is same as player
    // Check if two enemies have same position
    std::set<std::pair<int, int>> enemyPositions;
    for (auto e : enemies)
    {
        // Check if enemy pos is same as player
        if (e->getPosX() == xPlayer && e->getPosY() == yPlayer)
        {
            std::clog << "Player collided with enemy. Game Over" << std::endl;
            gameOver = true;
            break;
        }

        std::pair<int, int> pos = {e->getPosX(), e->getPosY()};
        // Check if position already exists in the set
        if (enemyPositions.count(pos))
        {
            std::clog << "Enemies have collided. Game Over" << std::endl;
            gameOver = true;
        }
        else
        {
            enemyPositions.insert(pos);
        }
    }

    // Check if all enemies are dead
    if (enemies.empty()) // And last round once implemented
    {
        // Trigger end of game
        std::clog << "All enemies are dead. Victory" << std::endl;
        victory = true;
    }

    // Leave game if vctory or game over
    if (gameOver || victory)
    {
        // TODO : Maybe make this a little nice, a message on the screen or something

        // For now going back at menu state
        Game::setState(new MenuState());
    }
}

void PlayStateOne::render()
{
    // Set a black background
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);

    // Render map
    // map->createBaseMap(windowHeight, windowWidth); // don't forget to comment out the map loading
    map->drawMap();

    // Render player
    player->draw();
    for (auto e : enemies)
    {
        e->draw();
    }

    SDL_RenderPresent(Game::renderer);
}

void PlayStateOne::processEvents(SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            Game::setState(new MenuState());
        }
        else
        {
            player->addEventToQueue(event);
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        player->addEventToQueue(event);
        break;
    }
}

void PlayStateOne::updateEnemies(std::vector<Enemy *> &enemies)
{

    // Iterate through the vector in reverse order
    // This way, removing elements doesn't affect the index of remaining elements
    for (int i = static_cast<int>(enemies.size()) - 1; i >= 0; i--)
    {
        if (player->getPosX() == enemies[i]->getPosX() && player->getPosY() == enemies[i]->getPosY())
        {
            // Remove the enemy player is on enemy position
            delete enemies[i];
            enemies.erase(enemies.begin() + i);

            // Check if they are enemies around
            // If so the enemy gets pushed by one cell and comes back
            // if it collides with another enemy, game over
            for (auto &enemy : enemies)
            {
                if (enemy->getPosX() >= player->getPosX() - 1 && enemy->getPosX() <= player->getPosX() + 1 &&
                    enemy->getPosY() >= player->getPosY() - 1 && enemy->getPosY() <= player->getPosY() + 1)
                {
                    // enemy won't move as it's going one cell further and comes back instantly
                    enemy->setNextToKilledEnemy(true);

                    // We need to check if during it's movement it collided with another enemy
                    int x = enemy->getPosX();
                    int y = enemy->getPosY();
                    int playerX = player->getPosX();
                    int playerY = player->getPosY();

                    // Test if aonther enemy at those positions
                    int newX = playerX + (x - playerX) * 2;
                    int newY = playerY + (y - playerY) * 2;

                    for (auto &e : enemies)
                    {
                        // Game over
                        if (e->getPosX() == newX && e->getPosY() == newY)
                        {
                            std::clog << "Enemies have collided. Game Over" << std::endl;
                            gameOver = true;
                            break;
                        }
                    }
                }
            }
            break;
        }
    }

    if (!gameOver)
    {
        // Update enemy position
        for (auto e : enemies)
        {
            e->update(player->getPosX(), player->getPosY());
        }
    }
}