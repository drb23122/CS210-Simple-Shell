#include "../include/input.h"

// Checks if the tokens was a built-in function.
// Returns 1 if the builtin command was executed, else 0 to continue
int check_builtin(char *tokens[INPUT_LEN]);

// returns the current system path
void getpath(char *tokens[INPUT_LEN]);

// sets the system path to the value at tokens[1]
void setpath(char *tokens[INPUT_LEN]);

// moves the cwd to the directory at tokens[1]
void cd(char *tokens[INPUT_LEN]);

// prints the history in order from oldest to newest
void print_history(char *tokens[INPUT_LEN]);
