#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char delimiters[] = " \t\n|><&;";

void print_prompt() {
  char cwd[100];
  getcwd(cwd, 100);

  printf(ANSI_GREEN "" ANSI_GREEN_BG "%s" GREEN_FG_BLUE_BG, getenv("USER"));
  printf("" ANSI_BLUE_BG "%s" ANSI_BLUE "", cwd);

  fflush(stdout); // Fix for prompt not printing correctly
}

void print_flashing_cursor() {
  printf(RED_BG_BLACK_BG BLINK "" ANSI_RED BLINK "" ANSI_RESET " ");
}

void remove_flashing_cursor(char *input) {
  printf("\33[A\33[2K\r");
  print_prompt();
  printf(RED_BG_BLACK_BG "" ANSI_RED "" ANSI_RESET " %s", input);

  fflush(stdout); // Fix for prompt not printing correctly
}

int get_input(char *input_buffer, char *output[INPUT_LEN]) {
  print_prompt();
  print_flashing_cursor();
  char *ret = fgets(input_buffer, INPUT_LEN, stdin);
  remove_flashing_cursor(input_buffer);

  // Exit if CTR-d pressed
  if (!ret) {
    return 0;
  }

  tokenize(input_buffer, output);
  // If input is empty
  if (!*output) {
    return 1;
  }

  // Exit if exit (and nothing else) inputted
  return (strcmp(output[0], "exit") || output[1]);
}

int tokenize(char input[INPUT_LEN], char *output[INPUT_LEN]) {
  // Check input is not empty
  if (!input) {
    return 1;
  }
  char *token = strtok_r(input, delimiters, &input);

  for (int i = 0; token; i++) {
    output[i] = token;
    token = strtok_r(input, delimiters, &input);
  }
  return 1;
}

int clear(char *array[INPUT_LEN]) {
  // Check array is not already empty
  if (!*array) {
    return 1;
  }
  for (int i = 0; array[i]; i++) {
    array[i] = NULL;
  }
  return 0;
}

void print_tokens(char *array[INPUT_LEN]) {
  printf("tokens: [");
  for (int i = 0; array[i]; i++) {
    printf("\"%s\"", array[i]);
    if (array[i + 1]) {
      printf(", ");
    }
  }
  printf("]\n");
}
