  #include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Chess.h"
// This C file contains the functions that will be used in the game state



void MovePieceOnBoard(int x, int y, int i , int j, char* promotion)
{  //Move <x,y> to <i,j> x

	struct Position pos = { -1, -1 }; 
	pos.x = (int)(x - 'a'); // 'translate' a-h to 0-7
	pos.y = y - (int)('1'); // 'translate' 1-8 to 0-7

	if (pos.x < 0 || pos.x>7 || pos.y < 0 || pos.y>7 ){
		if (console_or_gui == 0)
			printInvalidPos();
		else // gui mode
			//TODO open a window/popup in chess_gui that says the position is invalid
		return;
	}
	//TODO move piece if the move is valid

}

void GetMoves(int x, int y)
{ //call function from chess_logic

}

void GetBestMoves(int depth)
{
	//call function from chess_logic/ minimax
}

void GetScore(int depth, char* move)
{
	//call functions from chess_logic
}

void SaveToFile(char* fileName)
{
	//open a new file. 'w' for writing mode.
	FILE *fb = fopen(fileName, "w");  //TODO: add path before file name

	//xml decleration 
	fprintf(fb, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"); 


	fprintf(fb, "<game>\n");

	//---settings---
	fprintf(fb, "<next_turn>%s</next_turn>\n", next_player);
	fprintf(fb, "<game_mode>%d</game_mode>\n", game_mode);
	if (difficulty == DIFF_BEST)
		fprintf(fb, "<difficulty>best</difficulty>\n");
	else
		fprintf(fb, "<difficulty>%d</difficulty>\n", difficulty);
	fprintf(fb, "<user_color>%s</user_color>\n", user_color);

	//---board---
	fprintf(fb, "<board>\n");
	for (int i = 0; i < 8; i++) //for each row in the board
	{
		fprintf(fb, "<row_%d>", 8-i);

		for (int j = 0; j < 8; j++) //go for each col in the row and print 8 characters that represent the row's content.
		{
			char piece=board[i][j];
			if (piece==' ')
			{ //put the char '_' for an empty spot
				piece = '_';
			}
			fprintf(fb, "%c", piece);
		}
		fprintf(fb, "</row_%d>\n", 8-i);
	}
	fprintf(fb, "</board>\n");
	fprintf(fb, "</game>\n");

	//close the file
	fclose(fb);

}


