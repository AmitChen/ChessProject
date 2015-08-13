#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Chess.h"
#include "SDL.h"
#include "SDL_video.h"

int main(int argc, char* args[])
{
	SDL_Surface* image=NULL;
	SDL_Surface* screen = NULL;

	//start SDL
	SDL_Init(SDL_INIT_VIDEO);

	//SET UP SCREEN
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

	//load image
	image = SDL_LoadBMP("C:\\Users\\DELL\\Desktop\\kitty.bmp");

	//apply image to screen
	SDL_BlitSurface(image, NULL, screen, NULL);

	//update screen
	SDL_Flip(screen);
	
	//pause...
	SDL_Delay(5000);

	//free the loaded image
	SDL_FreeSurface(image);

	//quit SDL
	SDL_Quit();

	return 0;
}