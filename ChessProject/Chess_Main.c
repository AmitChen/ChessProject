#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Chess.h"
#include "SDL.h"
#include "SDL_video.h"
int console_or_gui = 0; // default mode is console

int main(int argc, char* args[])
{
	//chessprog is set to 0 for console mode 1 for console mode
	if (!strcmp("console", args[1])){
		console_or_gui = 0;
	}
	else{
		if (!strcmp("gui", args[1])){
			console_or_gui = 1;
		}
	}
	return 0;
}