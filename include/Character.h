#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Character 
{
    private:
        int healtPoint;

        int xPos, yPos;
        int xScreen, yScreen;

        SDL_Texture *charTexture;

    public:
        // Constructor / Destructor
        Character(int x, int y, const char* texPath);
        ~Character();

        // Getters
        int getHealthPoint() { return healtPoint; }

        // Setters
        void setHealthPoint(int hp) { healtPoint = hp; }
};