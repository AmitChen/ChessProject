#ifndef CHESS_H
#define CHESS_H


extern char* words[5];
int extern inputLeaks;
int extern game_mode;
int extern console_or_gui;
int extern difficulty;
extern char* firstPlayer;
#define BOARD_SIZE 8
char extern board[BOARD_SIZE][BOARD_SIZE];

void SettingsState();
void getInput();

void CommandLine();

//Command Line Functions:
void print_board();
void print_line();


//Setting State Functions:
void setGameMode(int mode);  //gets a mode value, 1 or 2, sets the game mode (a global variable) 
void setDifficulty(char* difficulty);
void setUserColor(char* color);
void loadGame(char* path);
void clearBoard();
void nextPlayer(char* next_player);
void removePiece(struct Position pos);
void setPiece(struct Position pos, char* piece);
void PrintBoard();
void quit();
void start();

//Game State Functions:



struct Position{
	int x;
	int y;
};



#endif