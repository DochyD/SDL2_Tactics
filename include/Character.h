#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Character
{
private:
    int healtPoint;

    int xPos, yPos;
    int xScreen, yScreen;

    SDL_Texture *charTexture;
    std::pair<int, int> charTextureDimension{45, 90};

public:
    // Constructor / Destructor
    Character(int hp, int x, int y, SDL_Texture *charTexture);
    ~Character();

    // Getters
    int getHealthPoint() { return healtPoint; }
    SDL_Texture *getCharTexture() { return charTexture; }
    std::pair<int, int> &getCharTextureDimension() { return charTextureDimension; }

    int getPosX() { return xPos; }
    int getPosY() { return yPos; }
    int getScreenX() { return xScreen; }
    int getScreenY() { return yScreen; }

    // Setters
    void setHealthPoint(int hp) { healtPoint = hp; }

    virtual void draw() = 0;
    virtual void update() = 0;
};