#include "../include/input.h"
#include <stdio.h>
#include <string.h>

const char delimiters[] = " \t\n|><&;";
int get_input(char output[INPUT_LEN]) {
  printf("--> ");

  char input_buffer[INPUT_LEN];
  // WARN: Check if n correct
  char *tmp = fgets(input_buffer, INPUT_LEN - 1, stdin);

  tokenize(input_buffer, output);

  return !((strcmp(output, "exit") == 0 || (tmp == NULL)));
}

void tokenize(char input[INPUT_LEN], char output[INPUT_LEN]) {
  char *token;
  token = strtok_r(input, delimiters, &input);

  printf("Tokens: [");
  while (token) {
    printf("\"%s\"", token);
    strlcat(output, token, INPUT_LEN);
    token = strtok_r(NULL, delimiters, &input);
    if (token) {
      printf(", ");
      strlcat(output, " ", INPUT_LEN);
    }
  }
  printf("]\n");
}
