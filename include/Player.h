#include <queue>
#include <vector>

#include "Character.h"

class Player : public Character
{
private:
    //int maxHealthPoint = 40;  
    std::queue<SDL_Event> eventQueue;

    std::vector<std::pair<int, int>> spellPreview;

public:
    // Constructor / Destructor
    Player(const Map& map, SDL_Texture *cTexture);
    ~Player(); // Use default destructor since base class handles texture

    void draw();
    void update();

    void processEventQueue();
    void addEventToQueue(SDL_Event e);

    //void castSpell();
    void spellOne();
    void spellTwo();
    void spellThree();
};