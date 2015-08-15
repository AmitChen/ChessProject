#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "Chess.h"
#include <windows.h>

int game_mode=1;
int difficulty = 1;
char* next_player = "white";
char* user_color = "white"; 
#define XML_ERROR "Error:the xml file is not in the correct format"


void setGameMode(int mode)
{
	game_mode = mode;
	//gets a mode value, 1 or 2, sets the game mode (a global variable)
}

// sets the difficulty ( only in player vs AI mode )
void setDifficulty(int diff)
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
	//reading line 3
	fgets(line, sizeof(file) * 50, file);
	setNextPlayer(findSubstring(line, "white", "black"));
	printf(next_player);
	Sleep(1000);
	// reading line 4
	fgets(line, sizeof(file) * 10, file);
	setGameMode(atoi(findSubstring(line, "1", "2")));
	Sleep(1000);
	// reading line 5
	fgets(line, sizeof(file) * 10, file);


}
char* findSubstring(char* line,char* opt1, char* opt2){
	if (strstr(line, opt1) != NULL){
		return opt1;
	}
	else{
		if (strstr(line, opt2) != NULL){
			return opt2;
		}
		else{
			printf(XML_ERROR);
			//TODO EXIT
		}
	}
	return NULL;
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

