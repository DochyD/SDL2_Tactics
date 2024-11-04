// C++ Standard Libraries
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"

int main()
{

	Game *game = nullptr;

	const char *WINDOW_NAME = "SDL2 Tactics";
	const float BASE_WINDOW_WIDTH = 1400;
	const float BASE_WINDOW_HEIGHT = 1050;

	const int FPS = 30;
	const int frameDuration = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// Init game
	game = new Game(WINDOW_NAME, BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT);

	// Game loop
	while (game->running())
	{

		// Fps managment
		frameStart = SDL_GetTicks();

		// Process events (user inputs/window resize)
		game->processEvents();

		// update game state
		game->update();

		// render game
		game->render();

		// Delay next iteration based on time left to reach next frame
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDuration > frameTime)
		{
			SDL_Delay(frameDuration - frameTime);
		}
	}

	// Call destructor > kill window/renderer/sdl...
	delete game;
}