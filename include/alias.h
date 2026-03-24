#include "../include/input.h"
#include <stdio.h>

// Max amount of aliases you can have
#define ALIAS_LEN 10

// Struct to store each alias
typedef struct {
  char *name;
  char *command[INPUT_LEN];
  int command_len;
} Alias;

// Check if alias in tokens, returns 0 to continue
int check_alias(char *tokens[INPUT_LEN]);

// Check if token will result in an infinite alias
int alias_invalid(char *token, int used[ALIAS_LEN]);

// Inserts a single alias into the tokens array, returns 0 if no more aliases found.
// Chars keeps track of the total length, to check for buffer overflows
int insert_alias(char *tokens[INPUT_LEN], int *chars);

// Create a new alias
int add_alias(char *tokens[INPUT_LEN]);

// Remove an alias
void remove_alias(char *tokens[INPUT_LEN]);

// Output all aliases, either to a file, or stdout
void output_aliases(FILE *stream);

// Load all aliases from .aliases file
void load_aliases();

// Save all aliases to .aliases file
void save_aliases();
