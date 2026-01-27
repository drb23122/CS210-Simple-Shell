#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char delimiters[] = " \t\n|><&;";

int get_input(char *output[INPUT_LEN]) {
  printf("--> ");
  fflush(stdout);

  char input_buffer[INPUT_LEN];
  // WARN: Check if n correct
  char *tmp = fgets(input_buffer, INPUT_LEN - 1, stdin);

  tokenize(input_buffer, output);

  return !((strcmp(output[0], "exit") == 0 || (tmp == NULL)));
}

void tokenize(char input[INPUT_LEN], char *output[INPUT_LEN]) {
  char *token = strtok_r(input, delimiters, &input);

  printf("Tokens: [");
  for (int i = 0; token; i++) {

    output[i] = token;
    printf("\"%s\"", output[i]);

    token = strtok_r(input, delimiters, &input);
    if (token) {
      printf(", ");
    }
  }
  printf("]\n");
}

int clear(char *input[INPUT_LEN]) {
  for (int i = 0; input[i]; i++) {
    input[i] = NULL;
  }
  return 0;
}
