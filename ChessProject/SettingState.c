#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Chess.h"

int game_mode=1;
int difficulty = 1;
char* firstPlayer = "white";
char* next_player;

void setGameMode(int mode)
{
	//gets a mode value, 1 or 2, sets the game mode (a global variable)
}

void setDifficulty(char* difficulty)
{

}

// the color of the human player in player vs AI mode
void setUserColor(char* color)
{

}

//loads from an xml file and sets the game data.
void loadGame(char* path)
{
	
}

//remove all pieces from the board
void clearBoard()
{

}

//which player plays first
void nextPlayer(char* next_player){

}

//removes a piece from the board
void removePiece(){


}

//prints the board to console
void print_board()
{
	int i, j;
	print_line();
	for (j = BOARD_SIZE - 1; j >= 0; j--)
	{
		printf((j < 9 ? " %d" : "%d"), j + 1);
		for (i = 0; i < BOARD_SIZE; i++){
			printf("| %c ", board[i][j]);
		}
		printf("|\n");
		print_line();
	}
	printf("   ");
	for (j = 0; j < BOARD_SIZE; j++){
		printf(" %c  ", (char)('a' + j));
	}
	printf("\n");
}