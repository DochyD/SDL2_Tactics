// Standard library
#include <iostream>
#include <stdexcept>
#include <utility>

// Project include
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Player.h"

// Initialize static member to nullptr (SDL not initialized yet)
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

int Game::windowWidth;
int Game::windowHeight;

// init those object to null because SDL is not initilized yet
Map *Game::map = nullptr;
Player *Game::player = nullptr;

// Constructor
Game::Game(const char *title, const int width, const int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Quit();
        throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
    {
        SDL_Quit();
        throw std::runtime_error("SDL could set filtering! SDL_Error: " + std::string(SDL_GetError()));
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        SDL_Quit();
        throw std::runtime_error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    // TODO : Handle window resize automatically
    // SDL_RenderSetLogicalSize(renderer, width, height);

    isRunning = true;
    windowWidth = width;
    windowHeight = height;

    // Create map / load map
    map = new Map();
    map->loadMap("base_map.json");

    // Load textures (that are not for the map)
    TextureManager::LoadBaseMapTextures();

    // Initiate player
    player = new Player(*map, TextureManager::playerTexture);

}

// Destructor
Game::~Game()
{

    TextureManager::DestroyBaseMapTextures();
    delete map;
    delete player;

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    // Quit SDL subsystems
    // IMG_Quit();
    SDL_Quit();
}

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

// Process window related events (eg : quitting game)
void Game::processEvents()
{
    // uncomment if feels slow when moving mouse.
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        // Quitting the game
        case SDL_QUIT:
            std::clog << "Event : Quit game." << std::endl;
            isRunning = false;
            return;
        // Resizing the window
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                std::clog << "Event : Window resized." << std::endl;
                windowWidth = event.window.data1;
                windowHeight = event.window.data2;
            }
            break;
        
        case SDL_KEYDOWN:
            player->addEventToQueue(event);
            break;

        case SDL_MOUSEBUTTONDOWN:
            player->addEventToQueue(event);
            break;
            // switch (event.button.button)
            // {
            // case SDL_BUTTON_LEFT:
            // {
            //     int x = event.button.x;
            //     int y = event.button.y;
            //     std::cout << "Left mouse button pressed at (" << x << ", " << y << ")" << std::endl;
            //     auto pos = map->findClickedCell(x, y);
                
            //     // if (pos.first != -99) // invalid pos
            //     // {
            //     //     auto screenPos = map->getScreenPos(pos.first, pos.second);
            //     //     player->setPos(pos.first, pos.second);
            //     //     player->setScreenPos(screenPos.first, screenPos.second);
            //     // }

            //     break;
            // }
            // default:
            //     std::cout << "Invalid mouse button pressed." << std::endl;
            //     break;
            // }
            // break;

        default:
            break;
        }
    }
}

// Update game state
void Game::update()
{
    // test
    player->update();
}

// Render game
void Game::render()
{
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Render map
    // map->createBaseMap(windowHeight, windowWidth); // don't forget to comment out the map loading
    map->drawMap();

    // Render player
    player->draw();

    SDL_RenderPresent(renderer);
}
