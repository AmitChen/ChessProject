#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "Chess.h"
#include <windows.h>
// This C file contains the functions that will be used in the setting state


int game_mode=1;
int difficulty = 1;
char* next_player = "white";
char* user_color = "white"; 
#define XML_ERROR "Error reading xml file"
#define MAX_LINE 100
//initialize counters for pieces on borad
int w_pawn=0;
int w_bishop=0;
int w_rook=0;
int w_knight=0;
int w_queen=0;
int w_king=0;
int b_pawn=0;
int b_bishop=0;
int b_rook=0;
int b_knight=0;
int b_queen=0;
int b_king=0;


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
//returns 1 if file exists
// returns 0 if file doesn't exists
int loadGame(char* fileName)
{
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
	char piece;
	for (int i = 7; i >= 0; i--){ // going through all lines in board
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
	w_pawn = 0;
	w_bishop = 0;
	w_rook = 0;
	w_knight = 0;
	w_queen = 0;
	w_king = 0;
	b_pawn = 0;
	b_bishop = 0;
	b_rook = 0;
	b_knight = 0;
	b_queen = 0;
	b_king = 0;
}

//which player plays first
void setNextPlayer(char* n_player){
	next_player = n_player;
}

//removes a piece from the board
void removePiece(struct Position pos){
	char piece = board[pos.x][pos.y];
	if (piece != EMPTY){
		decPieceCount(piece);
		board[pos.x][pos.y] = EMPTY;
	}
}

//sets a piece on the board
void setPiece(struct Position pos, char piece){

	incPieceCount(piece);
	if (checkBoard())
		board[pos.x][pos.y] = piece;
	else{
		printf(WRONG_POSITION);
		decPieceCount(piece);
	}
}

int checkKing(){
	if (w_king == 1 && b_king == 1)
		return 1;
	return 0; // not enough kings or too many kings ( second part should fail in checkBoard()
}

//checkBoard returns 1 if the board is valid, and 0 if the board has too many of a certain piece
int checkBoard(){
	if (w_king < 2 && w_queen < 2 && w_rook < 3 && w_knight < 3 && w_bishop < 3 && w_pawn < 9)
		if (b_king < 2 && b_queen < 2 && b_rook < 3 && b_knight < 3 && b_bishop < 3 && b_pawn < 9)
			return 1;
	return 0;
}

void incPieceCount(char piece){
	switch (piece){
	case W_PAWN:
		w_pawn++;
	case W_BISHOP:
		w_bishop++;
	case W_ROOK:
		w_rook++;
	case W_KNIGHT:
		w_knight++;
	case W_QUEEN:
		w_queen++;
	case W_KING:
		w_king++;
	case B_PAWN:
		b_pawn++;
	case B_BISHOP:
		b_bishop++;
	case B_ROOK:
		b_rook++;
	case B_KNIGHT:
		b_knight++;
	case B_QUEEN:
		b_queen++;
	case B_KING:
		b_king++;
	}
}

void decPieceCount(char piece){
	switch (piece){
	case W_PAWN:
		w_pawn--;
	case W_BISHOP:
		w_bishop--;
	case W_ROOK:
		w_rook--;
	case W_KNIGHT:
		w_knight--;
	case W_QUEEN:
		w_queen--;
	case W_KING:
		w_king--;
	case B_PAWN:
		b_pawn--;
	case B_BISHOP:
		b_bishop--;
	case B_ROOK:
		b_rook--;
	case B_KNIGHT:
		b_knight--;
	case B_QUEEN:
		b_queen--;
	case B_KING:
		b_king--;
	}
}

//initialize the board with the 32 pieces that starts a chess game
void InitFullBoard(){
	board[0][0] = B_ROOK;
	board[1][0] = B_KNIGHT;
	board[2][0] = B_BISHOP;
	board[3][0] = B_QUEEN;
	board[4][0] = B_KING;
	board[5][0] = B_BISHOP;
	board[6][0] = B_KNIGHT;
	board[7][0] = B_ROOK;
	for (int i = 0; i < 8; i++)
		board[i][1] = B_PAWN;
	board[0][7] = W_ROOK;
	board[1][7] = W_KNIGHT;
	board[2][7] = W_BISHOP;
	board[3][7] = W_QUEEN;
	board[4][7] = W_KING;
	board[5][7] = W_BISHOP;
	board[6][7] = W_KNIGHT;
	board[7][7] = W_ROOK;
	for (int i = 0; i < 8; i++)
		board[i][6] = W_PAWN;
}
