#pragma once

// C++ Standard Libraries
#include <vector>

// Third Party Libraries

// Project Specific headers
#include "Enemy.h"
#include "Map.h"
#include "Player.h"


#include "GameState.h"

class PlayStateOne : public GameState
{
private:
    // Game info
    int turns;
    float timer;
    bool gameOver = false;
    bool victory = false;

    const int numberOfWave = 5;
    const int enemiesPerWave = 5;

    // Map
    Map *map;

    // Player
    Player *player;
    
    //Enemies
    std::vector<Enemy *> enemies;

public:
    PlayStateOne();
    ~PlayStateOne();

    // Base GameState methods
    void init();
    void update() override;
    void render() override;
    void processEvents(SDL_Event &event) override;

    // Update enemies
    void updateEnemies(std::vector<Enemy *> &enemies);

};