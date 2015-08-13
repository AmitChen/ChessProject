#ifndef CHESS_H
#define CHESS_H


extern char* words[5];
int extern inputLeaks;
int extern game_mode;
int extern difficulty;
extern char* firstPlayer;
#define BOARD_SIZE 8
char extern board[BOARD_SIZE][BOARD_SIZE];

void SettingsState();
void getInput();
void setGameMode(int mode);  //gets a mode value, 1 or 2, sets the game mode (a global variable) 
void setDifficulty(char* difficulty);
void CommandLine();

//Setting State Functions:
void print_board();


//Game State Functions:



struct Position{
	int x;
	int y;
};



#endif