#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Chess.h"

char* words[5] = { NULL, NULL, NULL, NULL,NULL };
int inputLeaks = 0;

void CommandLine()
{
	printf("Enter game settings:\n");
	SettingsState();
	return 0;
}
void SettingsState(){
	//free all previous words before getting a new input
	for (int i = 0; i < 4; i++){
		if (words[i] != NULL){
			free(words[i]);
			inputLeaks--;
			words[i] = NULL;
		}
	}
	getInput();


	while (strcmp(words[0], "quit") && strcmp(words[0], "start"))  //main loop in setting state
	{
#pragma region game_mode

		if (!strcmp(words[0], "game_mode")){

			char* mode = EMPTY;

			if (!strcmp(words[1], "1")) //if user typed 1 for mode 
			{
				mode = "2 players";
				setGameMode(MODE_2PLAYERS); //send to settingState for update
			}
			else if (!strcmp(words[1], "2"))//if user typed 2 for mode
			{
				mode = "player vs. AI";
				setGameMode(MODE_PLAYER_VS_AI);//send to settingState for update
			}
			else
			{
				print_message("Wrong game mode\n");
			}

			print_message("Running game in %d mode\n", mode);
		}
#pragma endregion game_mode

#pragma region difficulty

		if (!strcmp(words[0], "difficulty")){
			if (game_mode != MODE_PLAYER_VS_AI)
			{
				print_message(ILLEGAL_COMMAND);
			}
			else
			{
				if (!strcmp(words[1], "best")) //if user typed 'best' for difficulty 
				{
					setDifficulty(DIFF_BEST);
				}
				else if (!strcmp(words[1], "depth"))
				{
					if (((int)strtof(words[2])>4) || ((int)strtof(words[2])<1)) //if depth isn't between 1 to 4
					{
						print_message("Wrong value for minimax depth. The value should be between 1 to 4\n");
					}
					else
					{
						setDifficulty((int)strtof(words[2]));
					}
				}

			}
		}

#pragma endregion difficulty

#pragma region user_color

		if (!strcmp(words[0], "user_color")){
			if (game_mode != MODE_PLAYER_VS_AI)
			{
				print_message(ILLEGAL_COMMAND);
			}
			else
			{ //TODO: ask if I can assume that user will always put black/white. or illigal value.
				setUserColor(words[1]);
			}
		}

#pragma endregion user_color

#pragma region load

		if (!strcmp(words[0], "load")){
			if (!loadGame(words[1]))
			{
				print_message("Wrong file name\n");
			}
			else
			{
				print_board(board);
			}
		}

#pragma endregion load

#pragma region clear

		if (!strcmp(words[0], "clear")){
			clearBoard();
		}

#pragma endregion clear

#pragma region next_player

		if (!strcmp(words[0], "next_player")){ //TODO: ask if I can assume that user will always put black/white. or illigal value.
			setNextPlayer(words[1]);
		}

#pragma endregion next_player

#pragma region remove

		if (!strcmp(words[0], "rm")){

			int x = (int)(words[1][1] - 'a');// char x is mapped to a position in the board [0.....7]
			int y = words[1][3] - (int)('1');
			struct Position pos = { x, y };
			if (x < 0 || x>7 || y < 0 || y>7){
				print_message(WRONG_POSITION);
			}
			else{
				removePiece(pos);
			}
		}

#pragma endregion remove

#pragma region set

		if (!strcmp(words[0], "set")){

			int x = (int)(words[1][1] - 'a');// char x is mapped to a position in the board [0.....7]
			int y = words[1][3] - (int)('1');
			struct Position pos = { x, y };
			if (x < 0 || x>7 || y < 0 || y>7){
				print_message(WRONG_POSITION);
			}
			else{
				char piece = EMPTY;
				
					if (!strcmp(words[3], "king"))
					{
						if (!strcmp(words[2], "white"))
							piece = W_KING;
						else if (!strcmp(words[2], "black"))
							piece = B_KING;
					}
					else if (!strcmp(words[3], "queen"))
					{
						if (!strcmp(words[2], "white"))
							piece = W_QUEEN;
						else if (!strcmp(words[2], "black"))
							piece = B_QUEEN;
					}
					else if (!strcmp(words[3], "rook"))
					{
						if (!strcmp(words[2], "white"))
							piece = W_ROOK;
						else if (!strcmp(words[2], "black"))
							piece = B_ROOK;
					}
					else if (!strcmp(words[3], "knight"))
					{
						if (!strcmp(words[2], "white"))
							piece = W_KNIGHT;
						else if (!strcmp(words[2], "black"))
							piece = B_KNIGHT;
					}
					else if (!strcmp(words[3], "bishop"))
					{
						if (!strcmp(words[2], "white"))
							piece = W_BISHOP;
						else if (!strcmp(words[2], "black"))
							piece = B_BISHOP;
					}
					else if (!strcmp(words[3], "pawn"))
					{
						if (!strcmp(words[2], "white"))
							piece = W_PAWN;
						else if (!strcmp(words[2], "black"))
							piece = B_PAWN;
					}
					else
					{
						print_message(ILLEGAL_COMMAND);
					}
				
			}
		}

#pragma endregion set

	} //end main loop of setting state

	if (strcmp(words[0], "quit"))
	{

	}
	else // "start"
	{

	}
}

//prints the board to console
void print_board(char some_board[BOARD_SIZE][BOARD_SIZE])
{
	int i, j;
	print_line();
	for (j = BOARD_SIZE - 1; j >= 0; j--)
	{
		printf((j < 9 ? " %d" : "%d"), j + 1);
		for (i = 0; i < BOARD_SIZE; i++){
			printf("| %c ", some_board[i][j]);
		}
		printf("|\n");
		print_line();
	}
	printf("   ");
	for (j = 0; j < BOARD_SIZE; j++){
		printf(" %c  ", (char)('a' + j));
	}
	printf("\n");
}

void print_line(){
	int i;
	printf("  |");
	for (i = 1; i < BOARD_SIZE * 4; i++){
		printf("-");
	}
	printf("|\n");
}

void getInput(){ // we get the input line from the user and return it as a 5 size array
	char c; // the next character to be read from user
	int j = 1; // counts the length of a word
	int k = 0; // index of the word in the word[] array [0,1,2,3,4];
	words[k] = (char*)calloc(1, sizeof(char)); //allocate one char to the first word
	inputLeaks++;
	assert(words[k] != NULL);
	c = '\0';
	while (c != '\n')
	{
		c = getc(stdin);     //read the input from keyboard standard input
		words[k] = (char*)realloc(words[k], j*sizeof(char)+1);    //re-allocate (resize) memory for character read to be stored
		assert(words[k] != NULL);
		if (c == ' '){
			c = getc(stdin);
			words[k][j - 1] = '\0';
			j = 1;
			k++;
			if (k >= 5){
				printf("too many arguments.. 6th word will be ignored");
				return;
			}
			words[k] = (char*)calloc(1, sizeof(char));
			inputLeaks++;
		}
		words[k][j - 1] = c;  //store read character by making pointer point to c
		j++;
	}
	words[k][j - 2] = '\0';   //at the end append null character to mark end of string
}


 
