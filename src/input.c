#include "../include/input.h"
#include <stdio.h>
#include <string.h>

const char delimiters[] = " \t\n|><&;";

int get_input(char *output[INPUT_LEN]) {
  printf("--> ");
  fflush(stdout); // Fix for prompt not printing correctly

  char input_buffer[INPUT_LEN];
  // WARN: Check if n correct
  char *tmp = fgets(input_buffer, INPUT_LEN - 1, stdin);
  // Exit if CTR-d pressed
  if (!tmp) {
    return 0;
  }

  tokenize(input_buffer, output);

  // Exit if exit (and nothing else) inputted
  return (strcmp(output[0], "exit") || output[1]);
}

void tokenize(char input[INPUT_LEN], char *output[INPUT_LEN]) {
  char *token = strtok_r(input, delimiters, &input);

  for (int i = 0; token; i++) {
    output[i] = token;
    token = strtok_r(input, delimiters, &input);
  }
}

int clear(char *array[INPUT_LEN]) {
  for (int i = 0; array[i]; i++) {
    array[i] = NULL;
  }
  return 0;
}
