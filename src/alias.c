#include "../include/alias.h"
#include "../include/env.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Alias *aliases[ALIAS_LEN];
int head_a = 0;

// Returns 0 to continue
int check_alias(char *tokens[INPUT_LEN]) {
  if (!tokens[0]) {
    return 1;
  }

  // If unalias entered then remove the alias
  if (!strcmp(tokens[0], "unalias")) {
    remove_alias(tokens);
    return 2;
  }

  // if alias entered
  if (!strcmp(tokens[0], "alias")) {
    // If alias by itself entered then output all aliases
    if (!tokens[1]) {
      output_aliases(stdout);
    }
    // else add a new alias
    else if (!add_alias(tokens)) {
      printf("Alias %s saved!\n", tokens[1]); // no error occured
    }
    return 2;
  }

  // check that each token won't result in an infinite alias
  for (int t = 0; tokens[t]; t++) {
    // make sure each alias can only be used once per token
    int used[ALIAS_LEN] = {0};
    if (alias_invalid(tokens[t], used)) {
      printf("Invalid alias: %s\n", tokens[t]);
      return 1;
    }
  }

  // Insert all aliases
  int chars = 0; // used to check the length won't overflow the buffer
  while (insert_alias(tokens, &chars)) {
  }

  return 0;
}

// Returns 1 if the token will alias infintely or will overflow buffer
int alias_invalid(char *token, int used[ALIAS_LEN]) {
  // Check if adding this will overflow the buffer

  for (int a = 0; a < head_a; a++) {
    if (!strcmp(token, aliases[a]->name)) {
      // Check if this alias has already been used -> infinite alias
      if (used[a]) {
        printf("Infinte alias detected!\n");
        return 1;
      }
      used[a] = 1;

      for (int c = 0; c < aliases[a]->command_len; c++) {
        if (alias_invalid(aliases[a]->command[c], used)) {
          return 1;
        }
      }
    }
  }
  return 0;
}

// returns 1 while aliases found
int insert_alias(char *tokens[INPUT_LEN], int *chars) {
  for (int tok_num = 0; tokens[tok_num]; tok_num++) {
    for (int ali_num = 0; ali_num < head_a; ali_num++) {
      if (!strcmp(tokens[tok_num], aliases[ali_num]->name)) {
        *chars = *chars - (int)strlen(tokens[tok_num]); // remove aliased word
        // If alias found then insert it
        int endpos = 0;
        for (; tokens[endpos]; endpos++) {
        } // Calculate position of last token in array
        endpos--;

        // Move elements forward out of the way
        int cmd_len = aliases[ali_num]->command_len;
        for (int k = endpos; k > tok_num; k--) {
          tokens[k + cmd_len - 1] = tokens[k];
        }

        // Insert new elements
        for (int k = 0; k < cmd_len; k++) {
          // check inserting word won't cause buffer overflow, +1 for space
          *chars = *chars + (int)strlen(aliases[ali_num]->command[k]) + 1;
          if (*chars >= INPUT_LEN) {
            printf("Buffer overflow detected!\n");
            return 1;
          }
          tokens[tok_num + k] = aliases[ali_num]->command[k]; // insert new word
        }

        return 1;
      }
    }
  }
  return 0;
}

int add_alias(char *tokens[INPUT_LEN]) {
  if (!tokens[1] || !tokens[2]) {
    printf("Alias must have name and command!\n");
    return 1;
  }

  // Checks if alias loaded from file is valid
  if (!tokens[0]) {
    return 1;
  }
  if (strcmp(tokens[0], "alias")) {
    printf("Invalid alias from file!\n");
    return 1;
  }

  for (int a = 0; a < head_a; a++) {
    if (!strcmp(aliases[a]->name, tokens[1])) {
      printf("Overriding alias %s\n", tokens[1]);
      remove_alias(tokens);
      break;
    }
  }

  if (head_a >= ALIAS_LEN) {
    printf("Cannot add any more aliases!\n");
    return 1;
  }

  aliases[head_a] = malloc(sizeof(Alias));

  aliases[head_a]->command_len = 0;
  aliases[head_a]->name = malloc((strlen(tokens[1]) + 1) * sizeof(char));
  strcpy(aliases[head_a]->name, tokens[1]);

  for (int i = 0; tokens[i + 2]; i++) {
    aliases[head_a]->command_len++;
    aliases[head_a]->command[i] =
        malloc((strlen(tokens[i + 2]) + 1) * sizeof(char));
    strcpy(aliases[head_a]->command[i], tokens[i + 2]);
  }

  head_a++;
  return 0;
}

void remove_alias(char *tokens[INPUT_LEN]) {
  if (!tokens[1]) {
    printf("Please provide the name of the alias you wish to remove!\n");
    return;
  }

  // find alias position
  int num = -1;
  for (int i = 0; i < head_a; i++) {
    if (!strcmp(tokens[1], aliases[i]->name)) {
      num = i;
      break;
    }
  }

  if (num == -1) {
    printf("Alias not found!\n");
    return;
  }
  printf("Unaliasing %s\n", tokens[1]);

  // remove old alias
  free(aliases[num]->name);
  for (int i = 0; i < aliases[num]->command_len; i++) {
    free(aliases[num]->command[i]);
    aliases[num]->command[i] = NULL;
  }
  free(aliases[num]);
  aliases[num] = NULL;
  // fill free space
  for (int i = num; i < head_a - 1; i++) {
    aliases[i] = aliases[i + 1];
  }
  head_a--;
}

void output_aliases(FILE *stream) {
  if (head_a == 0) {
    printf("No aliases have been set!\n");
  }
  for (int i = 0; i < head_a; i++) {
    fprintf(stream, "alias %s ", aliases[i]->name);
    for (int j = 0; j < aliases[i]->command_len; j++) {
      fprintf(stream, "%s ", aliases[i]->command[j]);
    }
    fprintf(stream, "\n");
  }
}

void load_aliases() {
  set_home();
  char buffer[INPUT_LEN];  // buffer for each line to be read to from file
  char *tokens[INPUT_LEN]; // pointers to each token in the buffer
  FILE *alias_file = fopen(".aliases", "r");
  if (alias_file) { // check that .alias_list exists
    while (fgets(buffer, INPUT_LEN, alias_file)) {
      tokenize(buffer, tokens);
      add_alias(tokens);
      clear(tokens);
    }
    fclose(alias_file);
  }
}

void save_aliases() {
  set_home();
  FILE *alias_file = fopen(".aliases", "w");
  output_aliases(alias_file); // print the list to the history file
  fclose(alias_file);
}
