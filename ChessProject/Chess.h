#ifndef CHESS_H
#define CHESS_H

#include "SDL.h"
#include "SDL_video.h"
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
#define NOT_YOUR_PIECE "The specified position does not contain your piece\n"



extern char* words[5];
int extern inputLeaks;
int extern moveLeaks;
int extern movesLeaks;
int extern game_mode;
int extern console_or_gui;
int extern difficulty;
extern char* next_player;// which player (1st or 2nd ) is playing now
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
void printInvalidPos();


//Setting State Functions:
void setGameMode(int mode);  //gets a mode value, 1 or 2, sets the game mode (a global variable) 
void setDifficulty(int diff);
void setUserColor(char* color);
int loadGame(char* path);
void clearBoard();
void setNextPlayer(char* n_player);
void removePiece(struct Position pos);
void setPiece(struct Position pos, char piece);
int checkBoard();
int checkKing();
void incPieceCount(char piece);
void decPieceCount(char piece);
char* findSubstring(char* line, char* opt1, char* opt2);
char* findDifficulty(char* line, char* opt1, char* opt2, char* opt3, char* opt4, char* opt5);
void InitFullBoard();

//Game State Functions:
void MovePieceOnBoard(int x, int y, int i, int j, char* promotion);
void GetMoves(int x, int y);
void GetBestMoves(int depth);
void GetScore(int depth, char* move);
void SaveToFile(char* fileName);
struct Move* createMove(int x, int y, int i, int j, char some_board[BOARD_SIZE][BOARD_SIZE], char promotion);



// GUI Functions:
void DrawGraficalUserInterface();
void drawBoard(SDL_Surface *screen);
char* getPieceBitmapFromBoard(char piece);


//Game Logic
void CopyBoard(char dest[BOARD_SIZE][BOARD_SIZE], char src[BOARD_SIZE][BOARD_SIZE]);
struct Position findKing(char* color, char some_board[BOARD_SIZE][BOARD_SIZE]);
int isBlack(char p);
int isWhite(char p);
struct Moves* PawnMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]);
struct Moves* BishopMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]);
struct Moves* RookMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]);
struct Moves* KnightMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]);
struct Moves* QueenMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]);
struct Moves* KingMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]);
void addMoveToMovesList(struct Move* move, struct Moves* moves);
void CopyMove(struct Move* moveDst, struct Move* moveSrc);
void concatMovesLists(struct Moves* moves1, struct Moves* moves2);
struct Moves* getMovesForPosition(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]);
int isPlayingColor(char p);

struct Position{
	int x;
	int y;
};

struct Move{
	struct Position src;
	struct Position dst;
	char* promotion;
	char board_after_move[BOARD_SIZE][BOARD_SIZE];
	struct Move* next;
	struct Move* prev;
};

struct Moves{
	struct Move* firstMove;
	struct Move* lastMove;
};


#endif