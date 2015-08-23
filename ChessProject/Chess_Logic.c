#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Chess.h"

char board[BOARD_SIZE][BOARD_SIZE];
int moveLeaks = 0;
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

			return whiteScore - blackScore;

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
		return PawnMoves(x, y, some_board);
	case W_BISHOP:
		return BishopMoves(x, y, some_board);
	case W_ROOK:
		return RookMoves(x, y, some_board);
	case W_KNIGHT:
		return KnightMoves(x, y, some_board);
	case W_QUEEN:
		return QueenMoves(x, y, some_board);
	case W_KING:
		return KingMoves(x, y, some_board);
	case B_PAWN:
		return PawnMoves(x, y, some_board);
	case B_BISHOP:
		return BishopMoves(x, y, some_board);
	case B_ROOK:
		return RookMoves(x, y, some_board);
	case B_KNIGHT:
		return KnightMoves(x, y, some_board);
	case B_QUEEN:
		return QueenMoves(x, y, some_board);
	case B_KING:
		return KingMoves(x, y, some_board);
		;
	}
	return moves;
}


struct Move* createMove(int x, int y, int i, int j, char some_board[BOARD_SIZE][BOARD_SIZE], char promotion){
	struct Move* move = calloc(1,sizeof(struct Move*));
	moveLeaks++;
	move->dst.x = i;
	move->dst.y = j;
	move->src.x = x;
	move->src.y = y;

	CopyBoard(move->board_after_move, some_board);
	move->board_after_move[i][j] = move->board_after_move[x][y];
	move->board_after_move[x][y] = EMPTY;
	move->next = NULL;
	move->prev = NULL;
	if (promotion != NULL){
		move->board_after_move[i][j] = promotion;
	}
	return move;
}

/////////////////////// The following functions are a "get moves" functions and they return a list of moves for a pieces


struct Moves* PawnMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]){
	struct Moves* moves = calloc(1,sizeof(struct Moves));
	movesLeaks++;
	struct Move* move;
	int isPromoted = 0;
	if (isWhite(some_board[x][y])){
		if (y + 1 == 7) isPromoted = 1; // promote the pawn 
		if (y + 1 <= 7 && some_board[x][y + 1] == EMPTY) // if you can move to an empty spot that is in the board
			if (isPromoted){

				move = createMove(x, y, x, y + 1, some_board, W_ROOK);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x, y + 1, some_board, W_KNIGHT);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x, y + 1, some_board, W_QUEEN);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x, y + 1, some_board, W_BISHOP);
				addMoveToMovesList(move, moves);
			}
			else{
				move = createMove(x, y, x, y + 1, some_board, NULL); // Move with no promotion
				addMoveToMovesList(move, moves);
			}

		if (y + 1 <= 7 && x - 1 >= 0 && isBlack(some_board[x-1][y+1])){ // can move  diagonal only if can eat a black piece
			if (isPromoted){

				move = createMove(x, y, x - 1, y + 1, some_board, W_ROOK);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x - 1, y + 1, some_board, W_KNIGHT);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x - 1, y + 1, some_board, W_QUEEN);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x - 1, y + 1, some_board, W_BISHOP);
				addMoveToMovesList(move, moves);
			}
			else{
				move = createMove(x, y, x - 1, y + 1, some_board, NULL); // Move with no promotion
				addMoveToMovesList(move, moves);
			}
		}

		if (y + 1 <= 7 && x + 1 <= 7 && isBlack(some_board[x+1][y+1])){
			if (isPromoted){

				move = createMove(x, y, x + 1, y + 1, some_board, W_ROOK);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x + 1, y + 1, some_board, W_KNIGHT);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x + 1, y + 1, some_board, W_QUEEN);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x + 1, y + 1, some_board, W_BISHOP);
				addMoveToMovesList(move, moves);
			}
			else{
				move = createMove(x, y, x + 1, y + 1, some_board, NULL); // Move with no promotion
				addMoveToMovesList(move, moves);
			}
		}
	}
	else{ // color is black
		if (y - 1 == 0) isPromoted = 1; // promote the pawn 
		if (y - 1 >= 0 && some_board[x][y - 1] == EMPTY) // if you can move to an empty spot that is in the board
			if (isPromoted){

				move = createMove(x, y, x, y - 1, some_board, W_ROOK);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x, y - 1, some_board, W_KNIGHT);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x, y - 1, some_board, W_QUEEN);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x, y - 1, some_board, W_BISHOP);
				addMoveToMovesList(move, moves);
			}
			else{
				move = createMove(x, y, x, y - 1, some_board, NULL); // Move with no promotion
				addMoveToMovesList(move, moves);
			}

		if (y - 1 >=0 && x - 1 >= 0 && isWhite(some_board[x - 1][y - 1])){ // can move  diagonal only if can eat a black piece
			if (isPromoted){

				move = createMove(x, y, x - 1, y - 1, some_board, W_ROOK);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x - 1, y - 1, some_board, W_KNIGHT);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x - 1, y - 1, some_board, W_QUEEN);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x - 1, y - 1, some_board, W_BISHOP);
				addMoveToMovesList(move, moves);
			}
			else{
				move = createMove(x, y, x - 1, y - 1, some_board, NULL); // Move with no promotion
				addMoveToMovesList(move, moves);
			}
		}

		if (y - 1 >= 0 && x + 1 <= 7 && isWhite(some_board[x + 1][y - 1])){
			if (isPromoted){

				move = createMove(x, y, x + 1, y - 1, some_board, W_ROOK);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x + 1, y - 1, some_board, W_KNIGHT);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x + 1, y - 1, some_board, W_QUEEN);
				addMoveToMovesList(move, moves);
				move = createMove(x, y, x + 1, y - 1, some_board, W_BISHOP);
				addMoveToMovesList(move, moves);
			}
			else{
				move = createMove(x, y, x + 1, y - 1, some_board, NULL); // Move with no promotion
				addMoveToMovesList(move, moves);
			}
		}
	}
	return moves;
}

struct Moves* BishopMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]){
	struct Moves* moves = calloc(1, sizeof(struct Moves));
	movesLeaks++;
	struct Move* move;
	int i, j;
	// check if can eat up-right
	i = x + 1;
	j = y + 1;
	while (i <= 7 && j <= 7){
		if (some_board[i][j] != EMPTY)
			break;
		else{
			move = createMove(x, y, i, j, some_board, NULL);  // add step to an empty spot on board
			addMoveToMovesList(move, moves);
		}
		i++;
		j++;
	}
	if (isWhite(some_board[x][y]) && i<=7 && j<=7 && isBlack(some_board[i][j])){ // white Bishop eats black piece
		move = createMove(x, y, i, j, some_board, NULL); 
		addMoveToMovesList(move, moves);
	}
	else{
		if (isBlack(some_board[x][y]) && i <= 7 && j <= 7 && isWhite(some_board[i][j])){ // black bishop eats white piece
			move = createMove(x, y, i, j, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
	}
	// check if can eat up-left
	i = x - 1;
	j = y + 1;
	while (i >=0 && j <= 7){
		if (some_board[i][j] != EMPTY)
			break;
		else{
			move = createMove(x, y, i, j, some_board, NULL);  // add step to an empty spot on board
			addMoveToMovesList(move, moves);
		}
		i--;
		j++;
	}
	if (isWhite(some_board[x][y]) && i >=0 && j <= 7 && isBlack(some_board[i][j])){ // white Bishop eats black piece
		move = createMove(x, y, i,j, some_board, NULL); 
		addMoveToMovesList(move, moves);
	}
	else{
		if (isBlack(some_board[x][y]) && i >= 0 && j <= 7 && isWhite(some_board[i][j])){ // black bishop eats white piece
			move = createMove(x, y, i, j, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
	}

	//check if can eat down-left
	i = x - 1;
	j = y - 1;
	while (i >=0 && j >=0){
		if (some_board[i][j] != EMPTY)
			break;
		else{
			move = createMove(x, y, i, j, some_board, NULL);  // add step to an empty spot on board
			addMoveToMovesList(move, moves);
		}
		i--;
		j--;
	}
	if (isWhite(some_board[x][y]) && i >= 0 && j >= 0 && isBlack(some_board[i][j])){ // white Bishop eats black piece
		move = createMove(x, y, i, j, some_board, NULL); 
		addMoveToMovesList(move, moves);
	}
	else{
		if (isBlack(some_board[x][y]) && i >= 0 && j >= 0 && isWhite(some_board[i][j])){ // black bishop eats white piece
			move = createMove(x, y, i, j, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
	}

	// check if can eat down-right
	i = x + 1;
	j = y - 1;
	while (i <= 7 && j >=0){
		if (some_board[i][j] != EMPTY)
			break;
		else{
			move = createMove(x, y, i, j, some_board, NULL);  // add step to an empty spot on board
			addMoveToMovesList(move, moves);
		}
		i++;
		j--;
	}
	if (isWhite(some_board[x][y]) && i <= 7 && j >= 0 && isBlack(some_board[i][j])){ // white Bishop eats black piece
		move = createMove(x, y, i,j, some_board, NULL);
		addMoveToMovesList(move, moves);
	}
	else{
		if (isBlack(some_board[x][y]) && i <= 7 && j >= 0 && isWhite(some_board[i][j])){ // black bishop eats white piece
			move = createMove(x, y, i, j, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
	}
	return moves;

}

struct Moves* RookMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]){
	struct Moves* moves = calloc(1, sizeof(struct Moves));
	movesLeaks++;
	struct Move* move;
	int i, j;
	// check if can eat up
	i = x;
	j = y + 1;
	while (j <= 7){
		if (some_board[i][j] != EMPTY)
			break;
		else{
			move = createMove(x, y, i, j, some_board, NULL);  // add step to an empty spot on board
			addMoveToMovesList(move, moves);
		}
		j++;
	}
	if (isWhite(some_board[x][y]) &&  j <= 7 && isBlack(some_board[i][j])){ // white rook eats black piece
		move = createMove(x, y, i, j, some_board, NULL);
		addMoveToMovesList(move, moves);
	}
	else{
		if (isBlack(some_board[x][y]) && j <= 7 && isWhite(some_board[i][j])){ // black rook eats white piece
			move = createMove(x, y, i, j, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
	}
	// check if can eat right
	i = x +1;
	j = y;
	while (i<=7){
		if (some_board[i][j] != EMPTY)
			break;
		else{
			move = createMove(x, y, i, j, some_board, NULL);  // add step to an empty spot on board
			addMoveToMovesList(move, moves);
		}
		i++;
	}
	if (isWhite(some_board[x][y]) && i <= 7&& isBlack(some_board[i][j])){ // white rook eats black piece
		move = createMove(x, y, i, j, some_board, NULL);
		addMoveToMovesList(move, moves);
	}
	else{
		if (isBlack(some_board[x][y]) && i <= 7 && isWhite(some_board[i][j])){ // black rook eats white piece
			move = createMove(x, y, i, j, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
	}

	//check if can eat down
	i = x;
	j = y - 1;
	while (j >= 0){
		if (some_board[i][j] != EMPTY)
			break;
		else{
			move = createMove(x, y, i, j, some_board, NULL);  // add step to an empty spot on board
			addMoveToMovesList(move, moves);
		}
		j--;
	}
	if (isWhite(some_board[x][y]) && j >= 0 && isBlack(some_board[i][j])){ // white rook eats black piece
		move = createMove(x, y, i, j, some_board, NULL);
		addMoveToMovesList(move, moves);
	}
	else{
		if (isBlack(some_board[x][y]) && j >= 0 && isWhite(some_board[i][j])){ // black rook eats white piece
			move = createMove(x, y, i, j, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
	}

	// check if can eat left
	i = x - 1;
	j = y;
	while (i >=0 ){
		if (some_board[i][j] != EMPTY)
			break;
		else{
			move = createMove(x, y, i, j, some_board, NULL);  // add step to an empty spot on board
			addMoveToMovesList(move, moves);
		}
		i--;
	}
	if (isWhite(some_board[x][y]) && i >= 0 && isBlack(some_board[i][j])){ // white Bishop eats black piece
		move = createMove(x, y, i, j, some_board, NULL);
		addMoveToMovesList(move, moves);
	}
	else{
		if (isBlack(some_board[x][y]) && i >= 0 && isWhite(some_board[i][j])){ // black bishop eats white piece
			move = createMove(x, y, i, j, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
	}
	return moves;
}

struct Moves* KnightMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]){
	struct Moves* moves = calloc(1, sizeof(struct Moves));
	movesLeaks++;
	struct Move* move;
	if (isWhite(some_board[x][y])){ // knight piece is white
		if (x - 2 >= 0){
			if (y - 1 >= 0 && (isBlack(some_board[x - 2][y - 1]) || some_board[x - 2][y - 1] == EMPTY)){
				move = createMove(x, y, x - 2, y - 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (y + 1 <= 7 && (isBlack(some_board[x - 2][y + 1]) || some_board[x - 2][y + 1] == EMPTY)){
				move = createMove(x, y, x - 2, y + 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
		if (x +2 <= 7){
			if (y - 1 >= 0 && (isBlack(some_board[x + 2][y - 1]) || some_board[x - 2][y - 1] == EMPTY)){
				move = createMove(x, y, x + 2, y - 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (y + 1 <= 7 && (isBlack(some_board[x + 2][y + 1]) || some_board[x - 2][y + 1] == EMPTY)){
				move = createMove(x, y, x + 2, y + 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
		if (y + 2 <= 7){
			if (x - 1 >= 0 && (isBlack(some_board[x - 1][y + 2]) || some_board[x - 1][y + 2] == EMPTY)){
				move = createMove(x, y, x - 1, y + 2, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (x + 1 <= 7 && (isBlack(some_board[x + 1][y + 2]) || some_board[x + 1][y + 2] == EMPTY)){
				move = createMove(x, y, x + 1, y + 2, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
		if (y - 2 >=0){
			if (x - 1 >= 0 && (isBlack(some_board[x - 1][y - 2]) || some_board[x - 1][y - 2] == EMPTY)){
				move = createMove(x, y, x - 1, y - 2, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (x + 1 <= 7 && (isBlack(some_board[x + 1][y - 2]) || some_board[x + 1][y - 2] == EMPTY)){
				move = createMove(x, y, x + 1, y - 2, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
	}
	else{ // knight piece is black
		if (x - 2 >= 0){
			if (y - 1 >= 0 && (isWhite(some_board[x - 2][y - 1]) || some_board[x - 2][y - 1] == EMPTY)){
				move = createMove(x, y, x - 2, y - 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (y + 1 <= 7 && (isWhite(some_board[x - 2][y + 1]) || some_board[x - 2][y + 1] == EMPTY)){
				move = createMove(x, y, x - 2, y + 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
		if (x + 2 <= 7){
			if (y - 1 >= 0 && (isWhite(some_board[x + 2][y - 1]) || some_board[x - 2][y - 1] == EMPTY)){
				move = createMove(x, y, x + 2, y - 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (y + 1 <= 7 && (isWhite(some_board[x + 2][y + 1]) || some_board[x - 2][y + 1] == EMPTY)){
				move = createMove(x, y, x + 2, y + 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
		if (y + 2 <= 7){
			if (x - 1 >= 0 && (isWhite(some_board[x - 1][y + 2]) || some_board[x - 1][y + 2] == EMPTY)){
				move = createMove(x, y, x - 1, y + 2, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (x + 1 <= 7 && (isWhite(some_board[x + 1][y + 2]) || some_board[x + 1][y + 2] == EMPTY)){
				move = createMove(x, y, x + 1, y + 2, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
		if (y - 2 >= 0){
			if (x - 1 >= 0 && (isWhite(some_board[x - 1][y - 2]) || some_board[x - 1][y - 2] == EMPTY)){
				move = createMove(x, y, x - 1, y - 2, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (x + 1 <= 7 && (isWhite(some_board[x + 1][y - 2]) || some_board[x + 1][y - 2] == EMPTY)){
				move = createMove(x, y, x + 1, y - 2, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
	}
	return moves;
}

struct Moves* QueenMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]){
	struct Moves* moves = calloc(1, sizeof(struct Moves));
	movesLeaks++;
	struct Moves* rookmoves = RookMoves(x, y, some_board);
	struct Moves* bishopmoves = BishopMoves(x, y, some_board);
	concatMovesLists(rookmoves, bishopmoves);
	return rookmoves;
}

struct Moves* KingMoves(int x, int y, char some_board[BOARD_SIZE][BOARD_SIZE]){
	struct Moves* moves = calloc(1, sizeof(struct Moves));
	movesLeaks++;
	struct Move* move;
	if (isWhite(some_board[x][y])){ // white king eats piece ( or moves to an empty spot )
		if (x + 1 <= 7){
			if (y + 1 <= 7 && (isBlack(some_board[x + 1][y + 1]) || some_board[x + 1][y + 1] == EMPTY)){
				move = createMove(x, y, x + 1, y + 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (isBlack(some_board[x + 1][y]) || some_board[x + 1][y] == EMPTY){
				move = createMove(x, y, x + 1, y, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (y - 1 >= 0 && (isBlack(some_board[x + 1][y - 1]) || some_board[x + 1][y - 1] == EMPTY)){
				move = createMove(x, y, x + 1, y - 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
		if (y - 1 >= 0 && (isBlack(some_board[x][y - 1]) || some_board[x][y - 1] == EMPTY)){
			move = createMove(x, y, x, y - 1, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
		if (y + 1 <= 7 && (isBlack(some_board[x][y + 1]) || some_board[x][y + 1] == EMPTY)){
			move = createMove(x, y, x, y + 1, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
		if (x - 1 >= 0){
			if (y + 1 <= 7 && (isBlack(some_board[x - 1][y + 1]) || some_board[x - 1][y + 1] == EMPTY)){
				move = createMove(x, y, x - 1, y + 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (isBlack(some_board[x - 1][y]) || some_board[x - 1][y] == EMPTY){
				move = createMove(x, y, x - 1, y, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (y - 1 >= 0 && (isBlack(some_board[x - 1][y - 1]) || some_board[x - 1][y - 1] == EMPTY)){
				move = createMove(x, y, x - 1, y - 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
	}
	else{ // black king eats piece ( or moves to an empty spot )
		if (x + 1 <= 7){
			if (y + 1 <= 7 && (isWhite(some_board[x + 1][y + 1]) || some_board[x + 1][y + 1] == EMPTY)){
				move = createMove(x, y, x + 1, y + 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (isWhite(some_board[x + 1][y]) || some_board[x + 1][y] == EMPTY){
				move = createMove(x, y, x + 1, y, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (y - 1 >= 0 && (isWhite(some_board[x + 1][y - 1]) || some_board[x + 1][y - 1] == EMPTY)){
				move = createMove(x, y, x + 1, y - 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
		if (y - 1 >= 0 && (isWhite(some_board[x][y - 1]) || some_board[x][y - 1] == EMPTY)){
			move = createMove(x, y, x, y - 1, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
		if (y + 1 <= 7 && (isWhite(some_board[x][y + 1]) || some_board[x][y + 1] == EMPTY)){
			move = createMove(x, y, x, y + 1, some_board, NULL);
			addMoveToMovesList(move, moves);
		}
		if (x - 1 >= 0){
			if (y + 1 <= 7 && (isWhite(some_board[x - 1][y + 1]) || some_board[x - 1][y + 1] == EMPTY)){
				move = createMove(x, y, x - 1, y + 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (isWhite(some_board[x - 1][y]) || some_board[x - 1][y] == EMPTY){
				move = createMove(x, y, x - 1, y, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
			if (y - 1 >= 0 && (isWhite(some_board[x - 1][y - 1]) || some_board[x - 1][y - 1] == EMPTY)){
				move = createMove(x, y, x - 1, y - 1, some_board, NULL);
				addMoveToMovesList(move, moves);
			}
		}
	}
	return moves;
}


//////////////// end of "get moves" functions for pieces

void CopyBoard(char dest[BOARD_SIZE][BOARD_SIZE], char src[BOARD_SIZE][BOARD_SIZE])
{
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			dest[i][j] = src[i][j];
		}
	}
}

int isBlack(char p){
	return (p == B_PAWN || p == B_KNIGHT || p == B_ROOK || p == B_BISHOP || p == B_QUEEN || p == B_KING);
}
int isWhite(char p){
	return (p == W_PAWN || p == W_KNIGHT || p == W_ROOK || p == W_BISHOP || p == W_QUEEN || p == W_KING);
}

//check if king of color 'color' is threatened
int isCheck(char* color, char some_board[BOARD_SIZE][BOARD_SIZE]){
	struct Position kingpos = findKing(color, some_board);
	
	//go through the list getAllMoves of the opposite_color and see if (i,j) equals kingpos.

}

void addMoveToMovesList(struct Move* move, struct Moves* moves){
	struct Move* moveToAdd = calloc(1,sizeof(struct Move*));
	moveLeaks++;
	CopyMove(moveToAdd,move);
	if (moves->firstMove == NULL){ // list is empty
		moves->firstMove = move;
		moves->lastMove = move;
	}
	else{
		moves->lastMove->next = move;
		moves->lastMove = move;
	}

}

// we extend moves1 by adding moves2 to it's last node
void concatMovesLists(struct Moves* moves1, struct Moves* moves2){
	moves1->lastMove->next = moves2->firstMove;
	moves1->lastMove = moves2->lastMove;
}

struct Position findKing(char* color, char some_board[BOARD_SIZE][BOARD_SIZE]){
	struct Position kingpos;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if ((!strcmp(color, "white")) && some_board[i][j] == W_KING){
				kingpos.x = i;
				kingpos.y = j;
				return kingpos;
			}
			if ((!strcmp(color, "black")) && some_board[i][j] == B_KING){
				kingpos.x = i;
				kingpos.y = j;
				return kingpos;
			}
		}
	}

}

void CopyMove(struct Move* moveDst,struct Move* moveSrc){
	CopyBoard(moveDst->board_after_move, moveSrc->board_after_move);
	moveDst->dst = moveSrc->dst;
	moveDst->src = moveSrc->src;
	moveDst->prev = moveSrc->prev;
	moveDst->next = moveSrc->next;
	moveDst->promotion = moveSrc->promotion;
}