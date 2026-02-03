#include "../include/history.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *history[INPUT_LEN][HIST_LEN];
int total = 0;

// returns 1 if history error, else zero
int check_hist(char *tokens[INPUT_LEN]) {
  if (!tokens[0]) {
    return 1;
  }

  if (tokens[0][0] == '!') {
    if (tokens[1]) {
      printf("History commands don't take arguments!\n");
      return 1;
    }

    char num_s[4];
    strncpy(num_s, tokens[0] + 1, 3);
    int num = atoi(num_s);
    if (num < -HIST_LEN || num > HIST_LEN) {
      printf("History goes from position -%d to %d!\n", HIST_LEN, HIST_LEN);
      return 1;
    }
    int pos;
    if (num > 0) {
      pos = num - 1;
    } else {
      pos = total + num;
    }

    for (int i = 0; history[pos][i]; i++) {
      tokens[i] = history[pos][i];
    }

    return 0;
  }

  add_hist(tokens);
  return 0;
}

int add_hist(char *input[INPUT_LEN]) {
  for (int i = 0; input[i]; i++) {
    history[total][i] = malloc((strlen(input[i]) + 1) * sizeof(char));
    strcpy(history[total][i], input[i]);
  }
  total++;
  return 0;
}

void print_hist() {
  printf("");
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
