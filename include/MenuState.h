#pragma once

// C++ Standard Libraries
#include <vector>
#include <string>

// Project Specific headers
#include "GameState.h"
#include "TextManagerMenu.h"


class MenuState : public GameState
{
private:
    // Text manager for the Menu
    TextMenu* textManager;

    std::vector<std::string> menuItems;
    int selectedItem;

    // Menu specific method
    void DrawTitle();
    void DrawMenuItems();

public:
    // Constructor / Destructor
    MenuState();
    ~MenuState();

    // Base methods
    void processEvents(SDL_Event &event) override;
    void update() override;
    void render() override;
};