#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Chess.h"

int game_mode=1;
int difficulty = 1;
char* firstPlayer = "white";
char* next_player;
char* user_color = "white"; // human user color default is white?


void setGameMode(int mode)
{
	game_mode = mode;
	//gets a mode value, 1 or 2, sets the game mode (a global variable)
}

// sets the difficulty ( only in player vs AI mode )
void setDifficulty(char* diff)
{
	difficulty = diff;
}

// the color of the human player ( only in player vs AI mode )
void setUserColor(char* color)
{
	user_color = color;
}

//loads from an xml file and sets the game data.
void loadGame(char* path)
{
	//TODO
}

//remove all pieces from the board
void clearBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			board[i][j] = EMPTY;
		}
	}
}

//which player plays first
void nextPlayer(char* n_player){
	next_player = n_player;
}

//removes a piece from the board
void removePiece(struct Position pos){

	board[pos.x][pos.y] = EMPTY;
}

//sets a piece on the board
void setPiece(struct Position pos, char* piece){

	board[pos.x][pos.y] = piece;
}


//print the board to screen
void PrintBoard(){
	print_board(board);
}

//frees all memory and terminates the program
void quit(){
	//TODO
}

//starts the game 
void start(){
	//TODO
}

