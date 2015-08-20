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

//  All the checks are done in Chess_CommandLine.c so (x,y) is a valid non-empty position on board
//TODO
struct Position getMovesForPosition(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]){

	char pieceToMove = some_board[x][y];
	switch (pieceToMove){ //TODO
	case W_PAWN:


	case W_BISHOP:

	case W_ROOK:

	case W_KNIGHT:

	case W_QUEEN:

	case W_KING:

	case B_PAWN:

	case B_BISHOP:

	case B_ROOK:

	case B_KNIGHT:

	case B_QUEEN:

	case B_KING:

		;
	}
}

int Score(char some_board[BOARD_SIZE][BOARD_SIZE], char* color){
	int whiteScore = 0;
	int blackScore = 0;
	char piece;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			piece = board[i][j];
			switch (piece){
			case W_PAWN:
				whiteScore += 1;
			case W_BISHOP:
				whiteScore += 3;
			case W_ROOK:
				whiteScore += 5;
			case W_KNIGHT:
				whiteScore += 3;
			case W_QUEEN:
				whiteScore += 9;
			case W_KING:
				whiteScore += 400;
			case B_PAWN:
				blackScore += 1;
			case B_BISHOP:
				blackScore += 3;
			case B_ROOK:
				blackScore += 5;
			case B_KNIGHT:
				blackScore += 3;
			case B_QUEEN:
				blackScore += 9;
			case B_KING:
				blackScore += 400;
		}
			if (!strcmp(color, "white"))
				return whiteScore - blackScore;
			else
				return blackScore - whiteScore;
	}
}