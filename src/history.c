#include "../include/history.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *history[HIST_LEN][INPUT_LEN];
int total = 0;

// returns 1 if error in parsing history command, else zero
int check_hist(char *tokens[INPUT_LEN]) {
  if (!tokens[0]) {
    return 1;
  }

  if (tokens[0][0] == '!') {
    if (tokens[1]) {
      printf("History commands don't take arguments!\n");
      return 1;
    }

    // Determint history number entered
    int pos;
    if (tokens[0][1] == '!') { // If !! entered
      pos = total;
    } else {
      char num_s[4];
      strncpy(num_s, tokens[0] + 1, 3);
      int num = atoi(num_s);
      if (num < -total || num > total || num == 0) {
        printf("History goes from position -%d to %d!\n", -total, total);
        return 1;
      }
      if (num > 0) {
        pos = num - 1;
      } else {
        pos = total + num;
      }
    }
    printf("Pos: %d\n", pos);

    // Subsitute history element into tokens input
    for (int i = 0; history[pos][i]; i++) {
      tokens[i] = history[pos][i];
    }

    return 0;
  }

  add_hist(tokens);
  return 0;
}

int add_hist(char *input[INPUT_LEN]) {

  if (total < HIST_LEN) {
    for (int i = 0; input[i]; i++) {
      history[total][i] = malloc((strlen(input[i]) + 1) * sizeof(char));
      strcpy(history[total][i], input[i]);
    }
    total++;
  } else {

    // Move each element forward one
    for (int i = 0; i < HIST_LEN - 1; i++) {
      for (int j = 0; j < INPUT_LEN; j++) {
        history[i][j] = history[i + 1][j];
      }
    }

    // Clear last element
    for (int i = 0; history[HIST_LEN - 1][i]; i++) {
      free(history[HIST_LEN - 1][i]);
      history[HIST_LEN - 1][i] = NULL;
    }

    for (int i = 0; input[i]; i++) {
      history[HIST_LEN - 1][i] = malloc((strlen(input[i]) + 1) * sizeof(char));
      strcpy(history[HIST_LEN - 1][i], input[i]);
    }
  }
  return 0;
}

void print_hist() {
  for (int i = 0; i < HIST_LEN; i++) {
    printf("%2d: ", i + 1);
    for (int j = 0; history[i][j]; j++) {
      printf("%s ", history[i][j]);
    }
    printf("\n");
  }
}

void free_hist() {
  for (int i = 0; i < HIST_LEN; i++) {
    for (int j = 0; history[i][j]; j++) {
      free(history[i][j]);
    }
  }
}
