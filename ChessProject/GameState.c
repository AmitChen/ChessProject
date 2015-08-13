  #include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Chess.h"


void MovePieceOnBoard(int x, int y, int i , int j, char* promotion)
{ //Move <x,y> to <i,j> x

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
	FILE *fb = fopen(fileName, "w");

	//xml decleration 
	fprintf(fb, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"); 


	fprintf(fb, "<game>\n");

	//---settings---
	fprintf(fb, "<next_turn> %d </next_turn>\n", nextPlayer);
	fprintf(fb, "<game_mode> %s </game_mode>\n", game_mode);
	fprintf(fb, "<difficulty> %s </difficulty>\n", difficulty);
	fprintf(fb, "<user_color> %s </user_color>\n", user_color);

	//---board---
	fprintf(fb, "<board>\n");
	for (int i = 0; i < 8; i++) //for each row in the board
	{
		fprintf(fb, "<row_%d>", i);

		for (int j = 0; j < 8; j++) //go for each col in the row and print 8 characters that represent the row's content.
		{
			char piece=board[i][j];
			if (!strcmp(piece, EMPTY))
			{ //put the char '_' for an empty spot
				piece = "_";
			}
			fprintf(fb, "%d", piece);
		}
		fprintf(fb, "</row_%d>\n", i);
	}
	fprintf(fb, "</board>\n");


	fprintf(fb, "</game>\n");

	//close the file
	fclose(fb);

}


