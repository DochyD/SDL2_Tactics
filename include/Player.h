

#include "Character.h"

class Player : public Character
{
private:
    //int maxHealthPoint = 40;  

public:
    // Constructor / Destructor
    Player(int hp, int x, int y, SDL_Texture *charTexture);
    ~Player(); // Use default destructor since base class handles texture

    void draw();
    void update();
};