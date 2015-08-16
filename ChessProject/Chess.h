#ifndef CHESS_H
#define CHESS_H

#define EMPTY ' '
#define W_PAWN 'm'
#define W_BISHOP 'b'
#define W_ROOK 'r'
#define W_KNIGHT 'n'
#define W_QUEEN 'q'
#define W_KING 'k'

#define B_PAWN 'M'
#define B_BISHOP 'B'
#define B_ROOK 'R'
#define B_KNIGHT 'N'
#define B_QUEEN 'Q'
#define B_KING 'K'

#define MODE_2PLAYERS 1
#define MODE_PLAYER_VS_AI 2
#define DIFF_BEST 5

#define perror_message(func_name) (perror("Error: standard function %s has failed", func_name))
#define print_message(message) (printf("%s", message));
#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define WRONG_POSITION "Invalid position on the board\n"



extern char* words[5];
int extern inputLeaks;
int extern game_mode;
int extern console_or_gui;
int extern difficulty;
extern char* next_player;
extern char* user_color;
#define BOARD_SIZE 8
char extern board[BOARD_SIZE][BOARD_SIZE];

int extern w_pawn;
int extern w_bishop;
int extern w_rook;
int extern w_knight;
int extern w_queen;
int extern w_king;
int extern b_pawn;
int extern b_bishop;
int extern b_rook;
int extern b_knight;
int extern b_queen;
int extern b_king;

void SettingsState();
void getInput();

void CommandLine();

//Command Line Functions:
void print_board(char some_board[BOARD_SIZE][BOARD_SIZE]);
void print_line();
void SettingsState();
void TransitionState();
void GameState();
void CommandLine();
void getInput();


//Setting State Functions:
void setGameMode(int mode);  //gets a mode value, 1 or 2, sets the game mode (a global variable) 
void setDifficulty(char* difficulty);
void setUserColor(char* color);
int loadGame(char* path);
void clearBoard();
void setNextPlayer(char* n_player);
void removePiece(struct Position pos);
void setPiece(struct Position pos, char* piece);
void PrintBoard();
void quit();
void start();
char* findSubstring(char* line, char* opt1, char* opt2);
char* findDifficulty(char* line, char* opt1, char* opt2, char* opt3, char* opt4, char* opt5);

//Game State Functions:
void SaveToFile(char* fileName);

// GUI Functions:
void DrawGraficalUserInterface();

struct Position{
	int x;
	int y;
};



#endif