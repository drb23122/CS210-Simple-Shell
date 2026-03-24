#include "../include/history.h"
#include "../include/alias.h"
#include "../include/env.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *history[HIST_LEN][INPUT_LEN]; // 2D array, each row represents a tokenized command line
int head = 0;                       // next available spot in the array (ciruclar implementation)

// check for history prompt and deal with current input
int check_history(char *tokens[INPUT_LEN]) {

  // if command line empty, return
  if (!tokens[0]) {
    return 1;
  }

  // check the first token is !
  if (tokens[0][0] == '!') {

    // check if a second token exists with history call
    if (tokens[1]) {
      printf("History doesn't take parameters!");
      return 1;
    }

    //checking for !!, !n, !-n
    int pos;

    //!!
    if (tokens[0][1] == '!') {

      // only '!!' can be entered
      if (tokens[0][2]) {
        printf("!! can only be called on it's own, with no extra input");
        return 1;
      }

      // else calculate the correct !! pos
      pos = (HIST_LEN + head - 1) % HIST_LEN;

    } else {

      // this code below generates either a positive or negative (!n or !-n)
      char num_s[4];
      strncpy(num_s, tokens[0] + 1, 3);
      int num = atoi(num_s);

      // boundary checking... if a valid int and if it's in range
      if (num <= -HIST_LEN || num > HIST_LEN || num == 0) {
        printf("You can only call to the last 20 commands, make sure you've "
               "entered a valid integer!\n");
        return 1;
      }

      // calculate the correct position
      // positive case
      if (num > 0) {
        if (history[head_hist][0]) {
          pos = (head_hist + num - 1) % HIST_LEN;
        } else
          pos = num - 1; // no overflow
      }
      // negative case
      else {
        pos = (HIST_LEN + head_hist + num) % HIST_LEN;
      }
    }

    // ensure that this position exists in the array
    if (!(history[pos][0])) {
      printf("No command in history location!\n");
      return 1;
    }

    //  Subsitute history element into tokens input
    for (int i = 0; history[pos][i]; i++) {
      tokens[i] = history[pos][i];
    }

    // Check if substitued value is alias
    check_alias(tokens);

    // at this point now, tokens conatins the executeable history command
    return 0;
  }
  
  //add current input line to history
  history_add(tokens);
  return 0;
}

//no history call has been made, add to history
void history_add(char *tokens[INPUT_LEN]) {

  // if circular occurs then have to free the element leaving array due to malloc
  for (int i = 0; history[head][i]; i++) {
    free(history[head][i]);
    history[head][i] = NULL;
  }

  //add the current token input to history
  for (int i = 0; tokens[i]; i++) {
    history[head][i] = malloc((strlen(tokens[i]) + 1) * sizeof(char));
    strcpy(history[head][i], tokens[i]);
  }

  //circular head implementation
  head = (head + 1) % HIST_LEN;
}

// printing history
void output_hist(FILE *stream) {
  int index = 1; // for printing the command number
  for (int i = 0; i < HIST_LEN; i++) {
    int pos = (head_hist + i) % HIST_LEN;
    if (history[pos][0]) { // if not empty then it must be the first element
      fprintf(stream, "%2d: ", index);
      index++;

      for (int j = 0; history[pos][j];
           j++) { // print each word in history entry
        fprintf(stream, "%s ", history[pos][j]);
      }
      fprintf(stream, "\n");
    }
  }
}

// loading histroy from file
void load_hist() {
  set_home();
  char buffer[INPUT_LEN + 4]; // buffer for each line to be read to from file
  char *tokens[INPUT_LEN];    // pointers to each token in the buffer
  FILE *hist_file = fopen(".hist_list", "r");
  if (hist_file) { // check that .hist_list exists
    while (fgets(buffer, INPUT_LEN, hist_file)) {
      tokenize(buffer + 4, tokens); // +4 to skip the number
      history_add(tokens);
      clear(tokens);
    }
    fclose(hist_file);
  }
}

// saving to history file
void save_hist() {
  set_home();
  FILE *hist_file = fopen(".hist_list", "w");
  output_hist(hist_file); // print the list to the history file
  fclose(hist_file);
}

// frees history when an exit command has been entered to the terminal
void free_hist() {
  for (int i = 0; i < HIST_LEN; i++) {
    for (int j = 0; history[i][j]; j++) {
      free(history[i][j]);
      history[i][j] = NULL;
    }
  }
}
