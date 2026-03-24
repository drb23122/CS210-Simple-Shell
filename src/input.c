#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//defining token delimiters
const char delimiters[] = " \t\n|><&;";

void print_prompt() {
  char cwd[100];
  getcwd(cwd, 100);
	
  //for fancy prompt output
  printf(BLUE_FG "" BLACK_FG BLUE_BG "%s" RESET, getenv("USER"));
  printf(BLUE_FG ORANGE_BG "" RESET ORANGE_BG "%s" ORANGE_FG BLACK_BG "",
         cwd);

  fflush(stdout); // Fix for prompt not printing correctly
}

//for fancy prompt
void print_flashing_cursor() {
  printf(PURPLE_BG BLACK_FG BLINK "" PURPLE_FG BLACK_BG "" RESET " ");
  fflush(stdout); // Fix for prompt not printing correctly
}

//for fancy prompt
void stop_flashing_cursor(char *tokens[INPUT_LEN]) {
  printf("\33[A\33[2K\r"); // move cursor up to previous line back to start
  print_prompt();

  //for fancy prompt
  printf(PURPLE_BG BLACK_FG "" PURPLE_FG BLACK_BG "" RESET " ");
  if (!tokens) {
    return;
  }
  for (int i = 0; tokens[i]; i++) {
    printf("%s ", tokens[i]);
  }
  printf("\n");

  fflush(stdout); // Fix for prompt not printing correctly
}

int get_input(char *input_buffer, char *output[INPUT_LEN]) {
  printf("\n"); // Can't put this in print_prompt or lines will be double spaced
  print_prompt();
  print_flashing_cursor();
  char *ret = fgets(input_buffer, INPUT_LEN, stdin); 	//get input from command line

  // Exit if CTR-d pressed
  if (!ret) {
    printf("\n"); // blank line above promt since no \n after CTR-d
    stop_flashing_cursor(NULL);
    printf("\n"); // put result under prompt
    return 0;
  }

  //call tokenize to split input into string tokens
  tokenize(input_buffer, output);
  stop_flashing_cursor(output);
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

//testing method
void print_tokens(char *tokens[INPUT_LEN]) {
  printf("tokens: [");
  for (int i = 0; tokens[i]; i++) {
    printf("\"%s\"", tokens[i]);
    if (tokens[i + 1]) {
      printf(", ");
    }
  }
  printf("]\n");
}
