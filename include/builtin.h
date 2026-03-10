#include "../include/input.h"

// Checks if the input was a built-in function.
// Returns 1 if the builtin command was executed, else 0 to continue
int check_builtin(char *input[INPUT_LEN]);

// returns the current system path
int getpath(char *input[INPUT_LEN]);

// sets the system path to the value at input[1]
int setpath(char *input[INPUT_LEN]);

// moves the cwd to the directory at input[1]
int cd(char *input[INPUT_LEN]);

// prints the history in order from oldest to newest
int print_history(char *input[INPUT_LEN]);

// prints the history in order from oldest to newest
int alias(char *input[INPUT_LEN]);

int print_aliases(char *input[INPUT_LEN]);
