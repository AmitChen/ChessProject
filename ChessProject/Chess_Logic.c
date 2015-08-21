#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Chess.h"

char board[BOARD_SIZE][BOARD_SIZE];
int movesLeaks = 0;


// ***Chess Logic ****
// moves and eats for each player ( user and computer ), possible moves, eats, scoring function, changes in the board.

void userMakeMove(){
	//TODO
}

void computerMakeMove(){
	//TODO
}

int Score(char some_board[BOARD_SIZE][BOARD_SIZE], char* color){
	int whiteScore = 0;
	int blackScore = 0;
	char piece;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			piece = board[i][j];
			switch (piece){
			case W_PAWN:
				whiteScore += 1;
			case W_BISHOP:
				whiteScore += 3;
			case W_ROOK:
				whiteScore += 5;
			case W_KNIGHT:
				whiteScore += 3;
			case W_QUEEN:
				whiteScore += 9;
			case W_KING:
				whiteScore += 400;
			case B_PAWN:
				blackScore += 1;
			case B_BISHOP:
				blackScore += 3;
			case B_ROOK:
				blackScore += 5;
			case B_KNIGHT:
				blackScore += 3;
			case B_QUEEN:
				blackScore += 9;
			case B_KING:
				blackScore += 400;
			}
			if (!strcmp(color, "white"))
				return whiteScore - blackScore;
			else
				return blackScore - whiteScore;
		}
	}
}

//  All the checks are done in Chess_CommandLine.c so (x,y) is a valid non-empty position on board
//TODO
struct Moves* getMovesForPosition(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]){
	struct Moves* moves = NULL;
	char pieceToMove = some_board[x][y];
	switch (pieceToMove){ //TODO
	case W_PAWN:

	case W_BISHOP:

	case W_ROOK:

	case W_KNIGHT:

	case W_QUEEN:

	case W_KING:

	case B_PAWN:

	case B_BISHOP:

	case B_ROOK:

	case B_KNIGHT:

	case B_QUEEN:

	case B_KING:
		;
	}
	return moves;
}


struct Move* createMove(int x, int y, int i, int j, char some_board[BOARD_SIZE][BOARD_SIZE], char promotion){
	struct Move* move = calloc(sizeof(struct Move*), 1);
	movesLeaks++;
	move->dst.x = i;
	move->dst.y = j;
	move->src.x = x;
	move->src.y = y;

	CopyBoard(move->board_after_move, some_board);
	move->board_after_move[i][j] = move->board_after_move[x][y];
	move->board_after_move[x][y] = EMPTY;
	move->next = NULL;
	if (promotion != NULL){
		move->board_after_move[i][j] = promotion;
	}
}

void PawnMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE],char* color){
	//white pawn moves. TODO ifs etc..
	struct Move* move;
	int isPromoted = 0;
	if (y +1 == 7) isPromoted = 1; // promote the pawn 
	if (y +1 <=7 && some_board[x][y + 1] == EMPTY) // if you can move to an empty spot that is in the board
		if (isPromoted){

			move = createMove(x, y, x, y + 1, some_board, W_ROOK);
			//Add move to list
			move = createMove(x, y, x, y + 1, some_board, W_KNIGHT);
			//Add move to list
			move = createMove(x, y, x, y + 1, some_board, W_QUEEN);
			//Add move to list
			move = createMove(x, y, x, y + 1, some_board, W_BISHOP);
			//Add move to list
		}
		else
			move = createMove(x, y, x, y + 1, some_board, NULL); // Move with no promotion
			//Add move to list

	if (y + 1 <=7 && x - 1 >= 0 && isBlack(x-1,y+1,some_board)){ // can move  diagonal only if can eat a black piece
		if (isPromoted){

			move = createMove(x, y, x - 1, y + 1, some_board, W_ROOK);
			//Add move to list
			move = createMove(x, y, x - 1, y + 1, some_board, W_KNIGHT);
			//Add move to list
			move = createMove(x, y, x - 1, y + 1, some_board, W_QUEEN);
			//Add move to list
			move = createMove(x, y, x - 1, y + 1, some_board, W_BISHOP);
			//Add move to list
		}
		else
			move = createMove(x, y, x - 1, y + 1, some_board, NULL); // Move with no promotion
			//Add move to list
	}

	if (y + 1 <=7 && x + 1 <=7){
		if (isPromoted){

			move = createMove(x, y, x + 1, y + 1, some_board, W_ROOK);
			//Add move to list
			move = createMove(x, y, x + 1, y + 1, some_board, W_KNIGHT);
			//Add move to list
			move = createMove(x, y, x + 1, y + 1, some_board, W_QUEEN);
			//Add move to list
			move = createMove(x, y, x + 1, y + 1, some_board, W_BISHOP);
			//Add move to list
		}
		else
			move = createMove(x, y, x + 1, y + 1, some_board, NULL); // Move with no promotion
		//Add move to list
	}
}

void CopyBoard(char dest[BOARD_SIZE][BOARD_SIZE], char src[BOARD_SIZE][BOARD_SIZE])
{
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			dest[i][j] = src[i][j];
		}
	}
}

int isBlack(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]){
	char p = some_board[x][y]; //p is the piece
	return (p == B_PAWN || p == B_KNIGHT || p == B_ROOK || p == B_BISHOP || p == B_QUEEN || p == B_KING);
}
int isWhite(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]){
	char p = some_board[x][y]; //p is the piece
	return (p == W_PAWN || p == W_KNIGHT || p == W_ROOK || p == W_BISHOP || p == W_QUEEN || p == W_KING);
}