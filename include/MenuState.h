#pragma once

// 
#include <vector>
#include <string>

#include "GameState.h"

class MenuState : public GameState
{
private:
    std::vector<std::string> menuItems;
    int selectedItem;

public:
    MenuState() : selectedItem(0)
    {
        menuItems = {"Level 1", "Level 2", "Level 3", "Options", "Quit"};
    }

    void update(Game *game) override;
    void render(Game *game) override;
    void processEvents(Game *game, SDL_Event &event) override;
};