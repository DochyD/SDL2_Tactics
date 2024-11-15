#pragma once


#include "GameState.h"

class PlayState : public GameState
{
private:
    int currentLevel;

public:
    explicit PlayState(int level) : currentLevel(level) {}

    void init();
    void update(Game *game) override;
    void render(Game *game) override;
    void processEvents(Game *game, SDL_Event &event) override;
};