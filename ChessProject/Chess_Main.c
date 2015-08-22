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
	
	DrawGraficalUserInterface(); 
	//Sleep(2000000);
	return 0;
}