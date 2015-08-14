#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "Chess.h"

int game_mode=1;
int difficulty = 1;
char* next_player = "white";
char* user_color = "white"; 


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
void loadGame(char* fileName)
{
	FILE *file = fopen(fileName, "r");
	char line[200]; // maximum length of a line is 200 chars
	for (int i = 0; i < 2; i++){ // skip first 2 lines
		while (fgetc(file) != '\n'){
			//do nothing . just skipping first 2 lines
		}
	}
	while ((fgets(line,sizeof(file), file)) != NULL) {
		printf("%s", &line); // for tests
		// do the actual reading here
	}
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
void setNextPlayer(char* n_player){
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

