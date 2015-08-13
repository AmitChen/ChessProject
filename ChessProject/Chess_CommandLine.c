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
	while (strcmp(words[0], "quit") && strcmp(words[0], "start"))
	{

	}
	if (strcmp(words[0], "quit"))
	{

	}
	else // "start"
	{

	}
}

//prints the board to console
void print_board()
{
	int i, j;
	print_line();
	for (j = BOARD_SIZE - 1; j >= 0; j--)
	{
		printf((j < 9 ? " %d" : "%d"), j + 1);
		for (i = 0; i < BOARD_SIZE; i++){
			printf("| %c ", board[i][j]);
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


 
