#include "SDL.h"
#include "SDL_video.h"
#include <string.h>
#include <stdio.h>
#include "Chess.h"


void DrawGraficalUserInterface()
{
	// gui window title testing
	int game_on = 1;
	SDL_Event event;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("Chess Game By Amit & Yehonatan", NULL);
	SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
	while (game_on) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			game_on = 0;


		// writing the ACTUAL game in gui
	}
	SDL_Quit();
}