#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"

class TextureManager{
    private:
        //Empty
    public:
        // Constructor/Destructor
        TextureManager();
        ~TextureManager();
        
        static SDL_Texture* LoadTexture(const char* fileName);
        static void DrawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);

};
