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
#define XML_ERROR "Error reading xml file"
#define MAX_LINE 100


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
//returns 1 if file exists and format is correct
// returns 0 if file doesn't exists or format is incurrect
int loadGame(char* fileName)
{
	PrintBoard();
	FILE *file = fopen(fileName, "r");
	if (file == NULL){
		printf(XML_ERROR);
		return 0;
	}
	char line[MAX_LINE]; // maximum length of a line is 100 chars
	for (int i = 0; i < 2; i++){ // skip first 2 lines
		while (fgetc(file) != '\n'){
			//do nothing . just skipping first 2 lines
		}
	}
	char* temp_value;
	//reading line 3 ( set next player )
	fgets(line, MAX_LINE, file);
	temp_value = findSubstring(line, "white", "black");
	if (temp_value != NULL)
		setNextPlayer(temp_value);
	// reading line 4 ( set game mode )
	fgets(line, MAX_LINE, file);
	temp_value = findSubstring(line, "1", "2");
	if (temp_value != NULL)
		setGameMode(atoi(temp_value));
	// reading line 5 ( set difficulty )
	fgets(line, MAX_LINE, file);
	char* diff = findDifficulty(line, "1", "2", "3", "4", "best");
	if (diff == NULL)
		setDifficulty(1);
	else{
		if (!strcmp(diff, "best"))
			setDifficulty(5);
		else
			setDifficulty(atoi(diff));
	}
	// reading line 6 ( set user color )
	fgets(line, MAX_LINE, file);
	temp_value = findSubstring(line, "white", "black");
	if (temp_value != NULL)
		setUserColor(temp_value);
	else
		setUserColor("white"); // user is white by default	
	while (fgetc(file) != '\n'){ // skipping line 7
		//do nothing . just skipping a line
	}
	// reading lines 8 to 1
	char* piece;
	for (int i = 7; i >= 0; i--){ // going through all lines in board
	//	fgets(line, MAX_LINE, file);
		while (fgetc(file) != '>'){ 
			//do nothing . skipping characters until getting to the pieces representation
		}
		for (int j = 0; j < 8; j++){
			piece = fgetc(file);
			if (piece == '_')
				board[j][i] = EMPTY;
			else
				board[j][i] = piece;
		}
		while (fgetc(file) != '\n'){ // finish reading the line
			//do nothing .
		}
	}
	return 1;
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
			return NULL;
			//TODO EXIT
		}
	}
	return NULL;
}

char* findDifficulty(char* line, char* opt1, char* opt2, char* opt3, char* opt4, char* opt5){
	if (strstr(line, opt1) != NULL){
		return opt1;
	}
	else{
		if (strstr(line, opt2) != NULL){
			return opt2;
		}
		else{
			if (strstr(line, opt3) != NULL){
				return opt3;
			}
			else{
				if (strstr(line, opt4) != NULL){
					return opt4;
				}
				else{
					if (strstr(line, opt5) != NULL){
						return opt5;
					}
					else{
						return NULL;
					}
				}
			}
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

