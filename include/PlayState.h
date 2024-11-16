#pragma once


#include "GameState.h"

class PlayState : public GameState
{
private:
    int currentLevel;

public:
    explicit PlayState(int level);
    ~PlayState();

    void init();
    void update() override;
    void render() override;
    void processEvents(SDL_Event &event) override;
};