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

  // Check each token won't be aliased infintely
  for (int t = 0; tokens[t]; t++) {
    int used[ALIAS_LEN];
    if (alias_invalid(tokens[t], used)) {
      printf("\"%s\" is an infinte alias!\n", tokens[t]);
      return 1;
    }
  }

  // Insert all aliases
  while (insert_alias(tokens)) {
  }

  return 0;
}

// Returns a 1 if the token will be aliased infintely
int alias_invalid(char *token, int used[ALIAS_LEN]) {
  for (int a = 0; a < head_a; a++) {
    if (!strcmp(token, aliases[a]->name)) {
      if (used[a]) {
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

// returns 0 while no aliases found
int insert_alias(char *tokens[INPUT_LEN]) {
  for (int tok_num = 0; tokens[tok_num]; tok_num++) {
    for (int ali_num = 0; ali_num < head_a; ali_num++) {
      if (!strcmp(tokens[tok_num], aliases[ali_num]->name)) {
        // If alias found then insert it
        int endpos = 0;
        for (; tokens[endpos]; endpos++) {
        } // Calculate position of last token in array
        endpos--;

        // Check new command won't be too long
        int cmd_len = aliases[ali_num]->command_len;
        if (endpos + cmd_len >= INPUT_LEN) {
          printf("Buffer length exceeded!\n");
          return 0;
        }

        // Move elements out of the way
        for (int k = endpos; k > tok_num; k--) {
          tokens[k + cmd_len - 1] = tokens[k];
        }
        // Insert new elements
        for (int k = 0; k < cmd_len; k++) {
          tokens[tok_num + k] = aliases[ali_num]->command[k];
        }

        return 1;
      }
    }
  }
  return 0;
}

void add_alias(char *tokens[INPUT_LEN]) {
  if (!tokens[1] || !tokens[2]) {
    printf("Alias must have name and command!\n");
    return;
  }
  if (head_a >= ALIAS_LEN) {
    printf("Cannot add any more aliases!\n");
    return;
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
