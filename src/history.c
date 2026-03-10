#include "../include/history.h"
#include "../include/env.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2D array, each row represents an input to the command line
char *history[HIST_LEN][INPUT_LEN]; // the command line, each part of this array
                                    // points to a string (token)
int head = 0;                       // next available spot in the array

// This method will be called when the input has been tokenised
// it's goal is to check that a history prompt has been entered and then execute
// the command
int check_history(char *tokens[INPUT_LEN]) {

  // if no commands, then just return
  // if they have entered an empty input, no need to check as invalid
  if (!tokens[0]) {
    return 1;
  }

  // check the first token is !- first sign of a valid history command
  if (tokens[0][0] == '!') {
    // history doesn't take parameters- invalid history prompt
    if (tokens[1]) {
      printf("History doesn't take parameters!\n");
      return 1;
    }

    // at this point, the command is at least valid whether history prompt or
    // normal command line
    int pos;
    if (tokens[0][1] == '!') {

      // only '!!' can be entered
      if (tokens[0][2]) {
        printf("!! can only be called on it's own, with no extra input\n");
        return 1;
      }

      // else calculate the correct !! pos
      pos = (HIST_LEN + head - 1) % HIST_LEN;
    } else {

      // this code below generates either a positive integer or a negative,
      // deependent on call
      char num_s[4];
      strncpy(num_s, tokens[0] + 1, 3);
      int num = atoi(num_s);

      // boundary checking
      // need to include boundary checking for negative num as can't access
      // negative index
      if (num <= -HIST_LEN || num > HIST_LEN || num == 0) {
        printf("You can only call to the last 20 commands!\n"); // TODO: Improve
                                                                // this message
        return 1;
      }

      // calculate the correct position
      // issue with this maths need to fix it to work circular

      // positie case
      if (num > 0) {
        // if overflow has occured
        // error as when full first time then this causes issues
        if (history[head][0]) {
          pos = (head + num - 1) % HIST_LEN; // TODO: Error with this line
        } else
          pos = num - 1; // no overflow
      }
      // negative case... !! = !-1
      else {
        pos = (HIST_LEN + head + num) % HIST_LEN;
      }
    }

    // ensure that this position exists in the array

    // this would cause an error
    if (!(history[pos][0])) {
      printf("No command in history location!\n");
      return 1;
    }

    // at this point, if the command isn't a history prompt then it will have
    // returned to main if it is a history prompt, then the maths above has
    // worked out the value to call

    // at this point, we are ready to interpret the command after Finlay's
    // mathematical expertise
    //  Subsitute history element into tokens input
    // this is making tokens[i] point the malloced strings in the corrosponding
    // array
    for (int i = 0; history[pos][i]; i++) {
      tokens[i] = history[pos][i];
    }

    // at this point now, tokens conatins the executeable history command
    return 0;
  }
  // if we get here, the command line should be added to the array
  history_add(tokens);
  return 0;
}

// This method is called when no history call has been made from the command
// line
void history_add(char *tokens[INPUT_LEN]) {

  // if circular occurs then have to free the element leaving the array of
  // structs
  for (int i = 0; history[head][i]; i++) {
    free(history[head][i]);
    history[head][i] = NULL;
  }

  // now we have freed position, need to add the current token input to history
  // current format- array of pointers to strings
  // malloc new space
  // repeat until tokens hit null
  for (int i = 0; tokens[i]; i++) {
    // here, you will have a current token
    history[head][i] = malloc((strlen(tokens[i]) + 1) * sizeof(char));
    strcpy(history[head][i], tokens[i]);
  }

  // head- next available position... circular implementation
  head = (head + 1) % HIST_LEN;
}

void output_hist(FILE *stream) {
  int index = 1; // for printing the command number
  for (int i = 0; i < HIST_LEN; i++) {
    int pos = (head + i) % HIST_LEN;
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

void save_hist() {
  set_home();
  FILE *hist_file = fopen(".hist_list", "w");
  output_hist(hist_file); // print the list to the history file
  fclose(hist_file);
}

// frees history when an exit command has been entered to the terminal
// gets access to the array as it's a global variable
void free_hist() {
  for (int i = 0; i < HIST_LEN; i++) {
    for (int j = 0; history[i][j]; j++) {
      free(history[i][j]);
      history[i][j] = NULL;
    }
  }
}
