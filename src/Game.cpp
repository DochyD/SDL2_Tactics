// Standard library
#include <iostream>
#include <stdexcept>

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
Character *Game::player = nullptr;

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

    // To handle window resize automatically
    // SDL_RenderSetLogicalSize(renderer, width, height);

    isRunning = true;
    windowWidth = width;
    windowHeight = height;

    // test zone
    map = new Map();
    map->loadMap("base_map.json");

    TextureManager::LoadCharacterTexture("assets/sprites/player.png");
    TextureManager::LoadEnemyTexture("assets/sprites/enemy.png");

    player = new Player(
        map->getPlayerBaseHealth(),
        map->getPlayerStartingPosX(),
        map->getPlayerStartingPosY(),
        TextureManager::playerTexture);

    std::cout << TextureManager::playerTexture << std::endl;
}

// Destructor
Game::~Game()
{

    TextureManager::DestroyTextures();
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

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                std::clog << "Event : Quit game." << std::endl;
                isRunning = false;
                return;

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    std::clog << "Event : Window resized." << std::endl;
                    windowWidth = event.window.data1;
                    windowHeight = event.window.data2;
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        std::cout << "Key 1 pressed." << std::endl;
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
                        std::cout << "Invalid key pressed." << std::endl;
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT: {
                        int x = event.button.x;
                        int y = event.button.y;
                        std::cout << "Left mouse button pressed at (" << x << ", " << y << ")" << std::endl;
                        map->findClickedCell(x, y);
                        
                        break;
                    }
                    default:
                        std::cout << "Invalid mouse button pressed." << std::endl;
                        break;
                }
                break;

            default:
                break;
        }
    }
}

// Update game state
void Game::update()
{
    // test
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
