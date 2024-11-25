// C++ Standard Libraries
#include <iostream>
#include <random>
#include <set>

// Project Specific headers
#include "MenuState.h"
#include "PlayStateOne.h"
#include "Game.h"
#include "TextureManager.h"

PlayStateOne::PlayStateOne()
{
    // Set up game variable
    turn = 1;
    timer = 0;
    gameOver = false;

    // Setup text manager
    textManager = new TextLevelOne();

    // Load map
    map = new Map();
    map->loadMap("base_map.json"); // handle texture loading

    // Load textures
    TextureManager::LoadBaseMapTextures();

    // Load player
    player = new Player(*map, TextureManager::playerTexture);


    // Load next batch of enemies
    GenerateNextEnemySpawn();

    // Load enemies ?? not sure that needed!

    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 16, 25));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 20, 16));

    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 16));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 17));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 14, 18));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 13, 19));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 12, 20));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 11, 21));

    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 16));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 14));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 15));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 17));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 18));
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

    // Start new turn
    if (newTurn)
    {
        // Go to next turn
        turn++;

        // Spawn enemies
        if (!nextWaveOfEnemies.empty())
        {
            std::cout << "Spawning enemies" << std::endl;
            SpawnNextBatchOfEnemies();

            nextWaveOfEnemies.clear();
        }

        // Generate next batch if needed
        if (turn < numberOfEnemyWave + 1)
        {
            GenerateNextEnemySpawn();
        }

        // Replenish player's ap
        player->replenishActionPoints();

        newTurn = false;
    }

    // Update player and enemies
    UpdatePlayerAndEnemies();

    // Check if enemy pos is same as player
    // Check if two enemies have same position (They collided)
    CheckIfGameOverFromEnemies();

    CheckPlayerOutOfHp();

    // Check if all enemies are dead
    CheckIfVictory();

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

    // Display info
    RenderTurn();
    RenderHealthPoint();
    RenderActionPoints();


    // Render map
    // map->createBaseMap(windowHeight, windowWidth); // don't forget to comment out the map loading
    map->drawMap();

    // Render enemy spawn
    DrawEnemySpawn();

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
        else if (event.key.keysym.sym == SDLK_F1 || event.key.keysym.sym == SDLK_SPACE)
        {
            // Start a new turn
            newTurn = true;
            std::cout << "New turn : " << turn << std::endl;
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

void PlayStateOne::UpdatePlayerAndEnemies()
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
        UpdateEnemies();
    }
}

void PlayStateOne::UpdateEnemies()
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

void PlayStateOne::CheckIfGameOverFromEnemies()
{

    int xPlayer = player->getPosX();
    int yPlayer = player->getPosY();

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
}

void PlayStateOne::CheckIfVictory()
{
    if (enemies.empty() && turn + 1 >numberOfEnemyWave)
    {
        // Trigger end of game
        std::clog << "All enemies are dead. Victory" << std::endl;
        victory = true;
    }
}

void PlayStateOne::CheckPlayerOutOfHp()
{
    if(player->getHealthPoint() <= 0)
    {
        std::clog << "Player ran out of healt points. Game over" << std::endl;
        gameOver = true;
    }
}

void PlayStateOne::GenerateNextEnemySpawn()
{
    // Create a random number generator
    std::random_device rd;  // Used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

    // Create a distribution within the specified range
    std::uniform_int_distribution<> distrib(0, map->getSize() - 1);

    int i = 0;

    while (i < enemiesPerWave)
    {
        int x = 0;
        int y = 0;
        while (map->isOutOfMap(x, y))
        {
            x = distrib(gen);
            y = distrib(gen);
        }
        nextWaveOfEnemies.push_back(std::make_pair(x, y));
        i++;
    }
}

void PlayStateOne::DrawEnemySpawn()
{
    // Draw player
    SDL_Rect srcRect, destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = map->getCellTextureDimension().first;
    srcRect.w = map->getCellTextureDimension().second;

    destRect.h = map->getCellTextureDimension().first;
    destRect.w = map->getCellTextureDimension().second;

    // TODO
    // resizing isn't being took care of here (based on the window's size)
    for (auto e : nextWaveOfEnemies)
    {
        auto pos = map->getScreenPos(e.first, e.second);
        destRect.x = pos.first;
        destRect.y = pos.second;
        TextureManager::DrawTexture(TextureManager::cellSpawn, srcRect, destRect);
    }
}

void PlayStateOne::SpawnNextBatchOfEnemies()
{
    // If there is already the player or an enemy on the cell, don't spawn it

    // Store current enetity pos
    std::set<std::pair<int, int>> currentEntityPos;
    currentEntityPos.insert(player->getPos());

    for(auto e: enemies)
    {
        currentEntityPos.insert(e->getPos());
    }

    // Spawn enemy there is no entity on the cell
    for(auto pos: nextWaveOfEnemies)
    {
        if (!currentEntityPos.count(pos))
        {
            enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, pos.first, pos.second));
        }
    }
}

void PlayStateOne::RenderTurn()
{
    // TODO : Do not hard code value
    textManager->RenderTurn(10, 10, turn);
}

void PlayStateOne::RenderHealthPoint()
{
    // TODO : Do not hard code value
    textManager->RenderHealthPoint(10, 50, player->getHealthPoint());
}

void PlayStateOne::RenderActionPoints()
{
    // TODO : Do not hard code value
    textManager->RenderActionPoint(150, 10, player->getCurrentActionPoints());
}

