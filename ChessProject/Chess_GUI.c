#include "SDL.h"
#include "SDL_video.h"
#include <string.h>
#include <stdio.h>
#include "Chess.h"

#define WIN_W 800
#define WIN_H 600
#define IMG_W 68
#define IMG_H 68


void DrawGraficalUserInterface()
{
	SDL_Event e;
	SDL_Rect rect_quit = { 592, 419, 202, 81 };
	SDL_Rect imgrect = { 30, 7, IMG_W, IMG_H };
	SDL_Surface *background = SDL_LoadBMP("Screen.bmp");
	SDL_Surface *piece = SDL_LoadBMP("piece.bmp");
	SDL_Surface *screen = SDL_SetVideoMode(WIN_W, WIN_H, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	int quit = 0;

	/* Initialize SDL and make sure it quits*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	//atexit(SDL_Quit);

	/* Create window surface*/

	if (screen == NULL) {
		printf("ERROR: failed to set video mode: %s\n", SDL_GetError());
		return 1;
	}

	/* Define the rects we need*/


	/* Load test spritesheet image*/

	if (background == NULL) {
		printf("ERROR: failed to load image: %s\n", SDL_GetError());
		return 1;
	}
	if (SDL_BlitSurface(background, NULL, screen, NULL) != 0) {
		SDL_FreeSurface(background);
		printf("ERROR: failed to blit image: %s\n", SDL_GetError());
		return 1;
	}
	if (SDL_BlitSurface(piece, NULL, screen, &imgrect) != 0) {
		SDL_FreeSurface(piece);
		printf("ERROR: failed to blit image: %s\n", SDL_GetError());
		return 1;
	}
	if (SDL_Flip(screen) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
		return 1;
	}

	while (!quit) {
		/* Clear window to BLACK*/

			/* Advance to next sprite*/
		if ((imgrect.x >= 30+IMG_H * 7) && (imgrect.y == 7+IMG_W * 7)){

		}
			imgrect.x += imgrect.w;
			if (imgrect.x >= 30+IMG_W * 8){
				if (SDL_BlitSurface(background, NULL, screen, NULL) != 0) {
					SDL_FreeSurface(background);
					printf("ERROR: failed to blit image: %s\n", SDL_GetError());
					return 1;
				}
				if (SDL_Flip(screen) != 0) {
					printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
					break;
				}
				imgrect.x = 30;
				imgrect.y += imgrect.h;
				if (imgrect.y >= 7+IMG_H * 8)
				{
					imgrect.y = 7;
				}
			}
			
			if (SDL_BlitSurface(piece, NULL, screen, &imgrect) != 0) {
				SDL_FreeSurface(piece);
				printf("ERROR: failed to blit image: %s\n", SDL_GetError());
				return 1;
			}
			/* We finished drawing*/
			if (SDL_Flip(screen) != 0) {
				printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
				break;
			}

			/* Poll for keyboard & mouse events*/

			while (SDL_PollEvent(&e) != 0) {
				switch (e.type) {
				case (SDL_QUIT) :
					quit = 1;
					break;
				case (SDL_KEYUP) :
					if (e.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					break;
				case (SDL_MOUSEBUTTONDOWN) :
					if ((e.button.x > rect_quit.x) && (e.button.x < rect_quit.x + rect_quit.w) && (e.button.y > rect_quit.y) && (e.button.y < rect_quit.y + rect_quit.h))
						quit = 1;
					break;
				default:
					break;
				}
			}

			/* Wait a little before redrawing*/
			SDL_Delay(100);
		}

		SDL_FreeSurface(background);
		return 0;
	}
