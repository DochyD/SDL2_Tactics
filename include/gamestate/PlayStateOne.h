#pragma once

// C++ Standard Libraries
#include <vector>

// Third Party Libraries

// Project Specific headers
#include "Enemy.h"
#include "Map.h"
#include "Player.h"
#include "TextManagerLevelOne.h"

#include "GameState.h"

class PlayStateOne : public GameState
{
private:
    // Game info
    int turn;
    float timer;
    bool gameOver = false;
    bool victory = false;
    bool newTurn = false;

    const int numberOfEnemyWave = 5;
    static constexpr int enemiesPerWave = 5;

    // Handle text rendering
    TextLevelOne *textManager;

    // Map
    Map *map;

    // Player
    Player *player;
    
    // Enemies
    std::vector<Enemy *> enemies;

    // Next enemies to spawn
    std::vector<std::pair<int, int>> nextWaveOfEnemies;

public:
    PlayStateOne();
    ~PlayStateOne();

    // Base GameState methods
    void init();
    void update() override;
    void render() override;
    void processEvents(SDL_Event &event) override;

    // Turn base method
    void GenerateNextEnemySpawn();
    void DrawEnemySpawn();
    void SpawnNextBatchOfEnemies();

    // Update entites
    void UpdatePlayerAndEnemies();
    void UpdateEnemies();

    // Check state of game 
    void CheckIfGameOverFromEnemies();
    void CheckIfVictory();
    void CheckPlayerOutOfHp();

    // Display info
    void RenderTurn();
    void RenderHealthPoint();

};