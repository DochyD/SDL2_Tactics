#include <bitset>
#include <queue>
#include <utility>
#include <vector>

#include "Character.h"

class Player : public Character
{
private:

    // Queue to hold events
    std::queue<SDL_Event> eventQueue;

    // Vector of cell on which we want to draw spell preview sprite on
    std::vector<std::pair<int, int>> clickableElements;

    // Know if spell is being used (full of 0 by default.)
    // Can contain 8 spells for now, can easily be upgraded if needed
    std::bitset<8> activatedSpells;


public:
    // Constructor / Destructor
    Player(const Map& map, SDL_Texture *cTexture);
    ~Player();

    // Basic  methods
    void draw();
    void update();

    // Events related methods
    void processEventQueue();
    void addEventToQueue(SDL_Event e) { eventQueue.push(e); };

    // Spell related methods
    void processClick(std::pair<int, int> pos);
    
    void addClickableElements(std::vector<std::pair<int, int>> elem);
    void previewSpellOne();
    void previewSpellTwo();
    void previewSpellThree();

    void castSpellOne(int x, int y);
    void castSpellTwo(int x, int y);
    void castSpellThree(int x, int y);

    void cleanSpells();
};