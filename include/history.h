// history header file
#include "../include/input.h"
#include <stdio.h>
#define HIST_LEN 20

// Check if a history command prompt has been entered
int check_history(char *tokens[INPUT_LEN]);

// if not history, add current command to the history
void history_add(char *tokens[INPUT_LEN]);

// free the malloced memory at the end when exit character entered
void free_hist();

// Print the history in order from oldest to newest to specified stream
void output_hist(FILE *stream);

// Load the history file
void load_hist();

// Save the history to the history file
void save_hist();

// Creates a separate copy of a token array so the original user input can be preserved 
void copy_tokens(char *src[INPUT_LEN], char *dst[INPUT_LEN]);

// Frees all dynamically allocated strings in a copied token array to avoid
// memory leaks once that temporary copy is no longer needed
void free_token_copy(char *tokens[INPUT_LEN]);