// Standard library
#include <iostream>
#include <stdexcept>
#include <utility>

// Project include
#include "GameState.h"
#include "Game.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"

// Initialize static member to nullptr (SDL not initialized yet)
SDL_Renderer *Game::renderer = nullptr;
GameState *Game::currentState = nullptr;
SDL_Event Game::event;

int Game::windowWidth;
int Game::windowHeight;

// init those object to null because SDL is not initilized yet
Map *Game::map = nullptr;
Player *Game::player = nullptr;

std::vector<Enemy *> enemies;

// Constructor
Game::Game(const char *title, const int width, const int height)
{
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Quit();
        throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
    }

    // Set render qulity to nearest when we rescale window
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
    {
        SDL_Quit();
        throw std::runtime_error("SDL could set filtering! SDL_Error: " + std::string(SDL_GetError()));
    }

    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        SDL_Quit();
        throw std::runtime_error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }

    // Initialize TTF (Truetype Font)
    if (TTF_Init() == -1)
    {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        throw std::runtime_error("TTF could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }

    // TODO : Handle window resize automatically
    // SDL_RenderSetLogicalSize(renderer, width, height);

    // Initialize Game variable
    isRunning = true;
    windowWidth = width;
    windowHeight = height;

    // Create map / load map
    // map = new Map();
    // map->loadMap("base_map.json");
    // levelGameOver = false;
    // // Load textures (that are not for the map)
    // TextureManager::LoadBaseMapTextures();

    // // Initiate player
    // player = new Player(*map, TextureManager::playerTexture);

    // //enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 16, 25));
    // //enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 20, 16));

    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 16));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 17));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 14, 18));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 13, 19));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 12, 20));
    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 11, 21));

    // enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 14));
    //  enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 15));
    //  enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 17));
    //  enemies.push_back(new Enemy(*map, TextureManager::enemyTexture, 15, 18));
}

// Destructor
Game::~Game()
{
    
    // Destroy textures
    // TODO make this line based on game state
    TextureManager::DestroyBaseMapTextures();

    // Destroy fonts, textures... loaded for a specific game state
    if (currentState)
    {
        delete currentState;
        currentState = nullptr;
    }

    // Destroy variables
    // TODO Should be moved to a destructod elsewhere.
    delete map;
    delete player;

    // Destroy renderer
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    // Destroy Window
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    // Quit SDL / SDL subsystems
    TTF_Quit();
    SDL_Quit();
}

// TODO : Handle window resize
void Game::handleResize(SDL_Event &event)
{
    int width = event.window.data1;
    int height = event.window.data2;

    // Update viewport to maintain aspect ratio
    float aspectRatio = 1280.0f / 720.0f;
    int newWidth = width;
    int newHeight = height;

    if (width / aspectRatio > height)
    {
        newWidth = static_cast<int>(height * aspectRatio);
    }
    else
    {
        newHeight = static_cast<int>(width / aspectRatio);
    }

    int vpX = (width - newWidth) / 2;
    int vpY = (height - newHeight) / 2;

    SDL_Rect viewport = {vpX, vpY, newWidth, newHeight};
    SDL_RenderSetViewport(renderer, &viewport);
}

// Set game state
void Game::setState(GameState *newState)
{
    if (currentState)
    {
        delete currentState;
    }
    currentState = newState;
}

void Game::update()
{
    if (currentState)
    {
        currentState->update();
    }
}

void Game::render()
{
    if (currentState)
    {
        currentState->render();
    }
}

void Game::processEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // std::cout << "event : " << event.type << std::endl;
        if (currentState)
        {
            currentState->processEvents(event);
        }

        // Handle global events (like window close)
        if (event.type == SDL_QUIT)
        {
            setRunning(false);
        }
    }
}

// // Process window related events (eg : quitting game)
// void Game::processEvents()
// {
//     // uncomment if feels slow when moving mouse.
//     SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

//     while (SDL_PollEvent(&event))
//     {
//         switch (event.type)
//         {
//         // Quitting the game
//         case SDL_QUIT:
//             std::clog << "Event : Quit game." << std::endl;
//             isRunning = false;
//             return;
//         // Resizing the window
//         case SDL_WINDOWEVENT:
//             if (event.window.event == SDL_WINDOWEVENT_RESIZED)
//             {
//                 std::clog << "Event : Window resized." << std::endl;
//                 windowWidth = event.window.data1;
//                 windowHeight = event.window.data2;
//             }
//             break;

//         case SDL_KEYDOWN:
//             player->addEventToQueue(event);
//             break;

//         case SDL_MOUSEBUTTONDOWN:
//             player->addEventToQueue(event);
//             break;

//         default:
//             break;
//         }
//     }
// }

// // Update game state
// void Game::update()
// {

//         // To check if the player's postion got updated
//         int xPlayer = player->getPosX();
//         int yPlayer = player->getPosY();

//         player->update();

//         // If the player pos got updated, then we need to update the enemies.
//         if (xPlayer != player->getPosX() || yPlayer != player->getPosY())
//         {
//             updateEnemies(enemies);
//         }

//         if (enemies.empty())
//         {
//             // Trigger end of game
//             std::cout << "ggwpezpz" << std::endl;
//         }

// }

// void Game::updateEnemies(std::vector<Enemy *> &enemies)
// {

//     // Iterate through the vector in reverse order
//     // This way, removing elements doesn't affect the index of remaining elements
//     for (int i = static_cast<int>(enemies.size()) - 1; i >= 0; i--)
//     {
//         if (player->getPosX() == enemies[i]->getPosX() && player->getPosY() == enemies[i]->getPosY())
//         {
//             // Remove the enemy player is on enemy position
//             delete enemies[i];
//             enemies.erase(enemies.begin() + i);

//             // Check if they are enemies around
//             // If so the enemy gets pushed by one cell and comes back
//             // if it collides with another enemy, game over
//             for (auto &enemy : enemies)
//             {
//                 if (enemy->getPosX() >= player->getPosX() - 1 && enemy->getPosX() <= player->getPosX() + 1 &&
//                     enemy->getPosY() >= player->getPosY() - 1 && enemy->getPosY() <= player->getPosY() + 1)
//                 {
//                     // enemy won't move as it's going one cell further and comes back instantly
//                     enemy->setNextToKilledEnemy(true);

//                     // We need to check if during it's movement it collided with another enemy
//                     int x = enemy->getPosX();
//                     int y = enemy->getPosY();
//                     int playerX = player->getPosX();
//                     int playerY = player->getPosY();

//                     // Test if aonther enemy at those positions
//                     int newX = playerX + (x - playerX) * 2;
//                     int newY = playerY + (y - playerY) * 2;

//                     for (auto &e : enemies)
//                     {
//                         // Game over
//                         if (e->getPosX() == newX && e->getPosY() == newY)
//                         {
//                             std::cout << "Game over collide" << std::endl;
//                             levelGameOver = true;
//                             break;
//                         }
//                     }
//                 }
//             }
//             break;
//         }
//     }

//     if (!levelGameOver)
//     {
//         // Update enemy position
//         for (auto e : enemies)
//         {
//             e->update(player->getPosX(), player->getPosY());
//         }
//     }

// }
// // Render game
// void Game::render()
// {
//     // Set a black background
//     SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
//     SDL_RenderClear(renderer);

//     // Render map
//     // map->createBaseMap(windowHeight, windowWidth); // don't forget to comment out the map loading
//     map->drawMap();

//     // Render player
//     player->draw();
//     for (auto e : enemies)
//     {
//         e->draw();
//     }

//     SDL_RenderPresent(renderer);
// }
