#pragma once

#include <bitset>
#include <queue>
#include <utility>
#include <vector>

#include "Character.h"

class Enemy : public Character
{

public:
    // Constructor / Destructor
    Enemy(const Map &map, SDL_Texture *cTexture);
    Enemy(const Map &map, SDL_Texture *cTexture, int x, int y);
    ~Enemy();

    // Basic  methods
    void draw();
    void update();
    void update(int playerX, int playerY);
};