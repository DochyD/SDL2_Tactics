#include "TextManager.h"

class TextMenu : public TextManager
{
private:

    // Fonts
    TTF_Font *robotoTitle = nullptr;
    TTF_Font *robotoRegular = nullptr;

    // Menu texts
    SDL_Texture *mainTitle = nullptr;
    SDL_Texture *level1Text = nullptr;
    SDL_Texture *level2Text = nullptr;
    SDL_Texture *level3Text = nullptr;
    SDL_Texture *settingsText = nullptr;
    SDL_Texture *quitGameText = nullptr;

public:
    // Constructor / Destructor
    TextMenu();
    ~TextMenu();

    // Virtual methods
    void LoadFonts() override;
    void DestroyFonts() override;
    void LoadTexts() override;
    void DestroyTexts() override;

    // Draw functions
    void DrawTitle(int x, int y);
    void DrawLevel1Text(int x, int y);
    void DrawLevel2Text(int x, int y);
    void DrawLevel3Text(int x, int y);
    void DrawSetting(int x, int y);
    void DrawQuit(int x, int y);

};