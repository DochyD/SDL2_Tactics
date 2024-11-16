#pragma once

//
#include <vector>
#include <string>

#include "GameState.h"
#include "TextManagerMenu.h"


class MenuState : public GameState
{
private:
    // Text manager for the Menu
    TextMenu textManager = TextMenu();

    std::vector<std::string> menuItems;
    int selectedItem;

public:
    // Constructor / Destructor
    MenuState();
    ~MenuState();

    // Base methods
    void processEvents(SDL_Event &event) override;
    void update() override;
    void render() override;

    // Menu specific method
    void DrawTitle();
    void DrawMenuItems();

};