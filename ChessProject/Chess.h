extern char* words[5];
int extern inputLeaks;
int extern game_mode;
int extern difficulty;
extern char* firstPlayer;


void SettingsState();
void getInput();
void setGameMode(int mode);  //gets a mode value, 1 or 2, sets the game mode (a global variable) 
void setDifficulty(char* difficulty);
void CommandLine();
