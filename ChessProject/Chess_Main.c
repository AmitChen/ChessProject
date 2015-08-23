#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Chess.h"
#include "SDL.h"
#include "SDL_video.h"
#include <windows.h>
int console_or_gui = 0; // default mode is console

int main(int argc, char* args[])
{
	// THIS IS IN COMMENT BECAUSE IT RECIEVES ARGUMENT FROM CONSOLE ( SOMETHING WE DON'T WISH TO APPLY NOW WHEN DEBUGGING )
	////chessprog is set to 0 for console mode 1 for console mode
	//if (!strcmp("console", args[1])){
	//	console_or_gui = 0;
	//}
	//else{
	//	if (!strcmp("gui", args[1])){
	//		console_or_gui = 1;
	//	}
	//}
	//	
	clearBoard();
//	loadGame("test.xml");
//	SaveToFile("test.xml");
	InitFullBoard();

	//print_board(board); /// for console
//	CommandLine();
	int x = 3, y = 4;
	board[x][y] = W_PAWN;
	board[x + 1][y + 1] = B_KNIGHT;
	board[x - 1][y + 1] = B_QUEEN;
	print_board(board);
	struct Moves* m= PawnMoves(x, y, board);
	struct Move* temp = m->firstMove;
	printf("<%d,%d> moves to :\n",x,y);
	while (temp != NULL){
		printf("<%d,%d>   ", temp->dst.x, temp->dst.y);
		temp = temp->next;
	}
//	DrawGraficalUserInterface(); 
	//Sleep(2000000);
		return 0;
}