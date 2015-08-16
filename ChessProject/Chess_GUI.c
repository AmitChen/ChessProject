#include "SDL.h"
#include "SDL_video.h"
#include <string.h>
#include <stdio.h>
#include "Chess.h"

#define WIN_W 800
#define WIN_H 600
#define IMG_W 70
#define IMG_H 70
void DrawGraficalUserInterface()
{
	SDL_Event e;
	SDL_Rect rect_quit = { 592, 419, 202, 81 };
	SDL_Rect imgrect;
	imgrect.x = 40;
	imgrect.y = 15;
	SDL_Surface *background = SDL_LoadBMP("Screen.bmp");
	SDL_Surface *piece = SDL_LoadBMP("piece.bmp");
	SDL_Surface *screen = SDL_SetVideoMode(WIN_W, WIN_H, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	int quit = 0;
	/* Initialize SDL and make sure it quits*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return ;
	}
	SDL_WM_SetCaption("Chess by Amit and Yehonatan", NULL);

	/* Create window surface*/

	if (screen == NULL) {
		printf("ERROR: failed to set video mode: %s\n", SDL_GetError());
		return ;
	}

	/* Define the rects we need*/


	/* Load test spritesheet image*/

	if (background == NULL) {
		printf("ERROR: failed to load image: %s\n", SDL_GetError());
		return ;
	}
	if (SDL_BlitSurface(background, NULL, screen, NULL) != 0) {
		SDL_FreeSurface(background);
		printf("ERROR: failed to blit image: %s\n", SDL_GetError());
		return ;
	}
	//if (SDL_BlitSurface(piece, NULL, screen, &imgrect) != 0) {
	//	SDL_FreeSurface(piece);
	//	printf("ERROR: failed to blit image: %s\n", SDL_GetError());
	//	return ;
	//}
	//if (SDL_Flip(screen) != 0) {
	//	printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	//	return ;
	//}

	while (!quit) {
		drawBoard(screen);

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
		SDL_Delay(400);
	}

	SDL_FreeSurface(background);
	return ;
}

void drawBoard(SDL_Surface *screen){
	char* pieceBitmap;
	SDL_Rect imgrect;
	imgrect.x = 40;
	imgrect.y = 15;
		for (int i = 7; i >= 0; i--){
			for (int j = 0; j < 8; j++)
			{
				pieceBitmap = getPieceBitmapFromBoard(board[i][j]);
				if (!strcmp(pieceBitmap, "empty"))
					continue;
				SDL_Surface *piece = SDL_LoadBMP(pieceBitmap);
				imgrect.x = 40 + i*IMG_H;
				imgrect.y = 15 + (7-j)*IMG_W;
				if (SDL_BlitSurface(piece, NULL, screen, &imgrect) != 0) {
					SDL_FreeSurface(piece);
					printf("ERROR: failed to blit image: %s\n", SDL_GetError());
					return ;
				}
				/* We finished drawing*/
				if (SDL_Flip(screen) != 0) {
					printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
					return ;
				}
			}
		}
}

char* getPieceBitmapFromBoard(char piece){
	switch (piece){
	case W_PAWN:
		return "w_pawn.bmp";
	case W_BISHOP:
		return "w_bishop.bmp";
	case W_ROOK:
		return "w_rook.bmp";
	case W_KNIGHT:
		return "w_knight.bmp";
	case W_QUEEN:
		return "w_queen.bmp";
	case W_KING:
		return "w_king.bmp";
	case B_PAWN:
		return "w_pawn.bmp";
	case B_BISHOP:
		return "b_bishop.bmp";
	case B_ROOK:
		return "b_rook.bmp";
	case B_KNIGHT:
		return "b_knight.bmp";
	case B_QUEEN:
		return "b_queen.bmp";
	case B_KING:
		return "b_king.bmp";
	case EMPTY:
		return "empty";
	}
	return "empty";
}