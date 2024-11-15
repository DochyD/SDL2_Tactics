// C++ Standard Libraries
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>

// Third Party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Constants
#include "define.h"

// Project Specific headers
#include "Game.h"
#include "MenuState.h"

int main()
{
	// Init game
	Game game = Game(WINDOW_NAME, BASE_WINDOW_WIDTH, BASE_WINDOW_HEIGHT);
	game.setState(new MenuState());

	// Set game state to MAIN_MENU

	// Variable for fps managment
	Uint32 frameStart;
	int frameTime;

	// Game loop
	while (game.running())
	{

		// Get tick mesure process duration latter
		frameStart = SDL_GetTicks();

		// Game logic
		game.processEvents();
		game.update();
		game.render();

		// Delay next iteration based on time left to reach next frame
		frameTime = SDL_GetTicks() - frameStart;
		if (FRAME_DURATION > frameTime)
		{
			SDL_Delay(FRAME_DURATION - frameTime);
		}
	}

	// SDL ressources are cleaned up inside the Game object's destructor
	return 0;
}