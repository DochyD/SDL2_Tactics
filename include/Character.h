#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Map.h"

class Character
{
private:
    int healtPoint;

    int xPos, yPos;
    int xScreen, yScreen;

    SDL_Texture *charTexture;
    std::pair<int, int> charTextureDimension{45, 90};

    // Ref to the map.
    const Map& map;

public:
    // Constructor / Destructor
    Character(const Map& map, SDL_Texture *cTexture);
    ~Character();

    // Getters
    int getHealthPoint() { return healtPoint; }
    int getPosX() { return xPos; }
    int getPosY() { return yPos; }
    int getScreenX() { return xScreen; }
    int getScreenY() { return yScreen; }

    // Setters
    void setHealthPoint(int hp) { healtPoint = hp; }
    void setPos(int x, int y) { xPos = x; yPos = y; }
    void setScreenPos(int x, int y) { xScreen = x; yScreen = y; }

    // Texture 
    SDL_Texture *getCharTexture() { return charTexture; }
    std::pair<int, int> &getCharTextureDimension() { return charTextureDimension; }

    // Basic methods
    virtual void draw() = 0;
    virtual void update() = 0;
};