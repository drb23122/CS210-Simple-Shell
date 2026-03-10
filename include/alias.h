#include "../include/input.h"
#include <stdio.h>

#define ALIAS_LEN 10

typedef struct {
  char *name;
  char *command[INPUT_LEN];
  int command_len;
} Alias;

int check_alias(char *tokens[INPUT_LEN]);
int alias_invalid(char *token, int used[ALIAS_LEN]);
int insert_alias(char *tokens[INPUT_LEN]);
void add_alias(char *tokens[INPUT_LEN]);
void remove_alias(char *tokens[INPUT_LEN]);
void output_aliases(FILE *stream);
void load_aliases();
void save_aliases();
