#include "../include/builtin.h"
#include "../include/env.h"
#include "../include/execute.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *wel =
    "This is the SUSHI Shell - Strathclyde Unix-type SHell Implementation \n"
    "⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣤⣤⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⣠⣴⣾⣿⡿⠿⠛⠛⠛⠛⠛⠛⠛⠻⠿⢿⣿⣶⣤⣄⠀⠀\n"
    "⢠⣾⡿⠛⠉⠀⠀⠀⠀⣀⣀⣀⣀⣀⣀⠀⠀⠀⠀⠉⠛⢿⣷⡀\n"
    "⣿⣿⠀⠀⠀⠀⠀⢶⣿⣿⣿⣿⣿⣿⣿⣿⡶⠀⠀⠀⠀⠈⣿⣷\n"
    "⣿⣿⣷⣄⡀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⢀⣠⣾⣿⣿\n"
    "⣿⣿⣿⣿⣿⣿⣶⣦⣤⣤⣤⣄⣠⣤⣤⣤⣴⣶⣿⣿⣿⣿⣿⣿\n"
    "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
    "⣿⣿⣿⣿⣿⣿⣿⡿⠛⢿⣿⣿⣿⣿⡿⠛⢿⣿⣿⣿⣿⣿⣿⣿\n"
    "⣿⣿⣿⣿⣿⣿⣿⣿⣦⣾⣿⣿⣿⣿⣷⣴⣿⣿⣿⣿⣿⣿⣿⣿\n"
    "⢻⣿⣿⣿⣿⣿⣿⣏⠀⠉⠛⠛⠛⠛⠉⠀⣹⣿⣿⣿⣿⣿⣿⡟\n"
    "⠀⠻⣿⣿⣿⣿⣿⣿⣿⣶⣦⣤⣤⣴⣶⣿⣿⣿⣿⣿⣿⣿⠟⠀\n"
    "⠀⠀⠈⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠋⠁⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠉⠉⠙⠛⠛⠛⠛⠋⠉⠉⠀⠀⠀⠀⠀⠀⠀\n"
    "\n";

int main(void) {
  printf("%s", wel);

  char *saved_path[2] = {NULL, save_path()}; // stored in form of input
  printf("Saved path: %s\n", saved_path[1]);

  char cwd[100];
  getcwd(cwd, 100);
  printf("Old HOME: %s\n", cwd);
  set_home();
  getcwd(cwd, 100);
  printf("New HOME: %s\n", cwd);

  char input_buffer[INPUT_LEN]; // Buffer for user input
  char *tokens[INPUT_LEN];      // Pointers to each token in buffer
  clear(tokens); // Clears data left over from previous run which causes errors

  while (get_input(input_buffer, tokens)) {
    // print_tokens(tokens); // Uncomment for debugging
    if (!check_builtin(tokens)) {
      run(tokens);
    }

    clear(tokens);
  }
  printf("\nSushi says argato!\n");

  // Cleaning up
  setpath(saved_path);
  free(saved_path[1]);
  printf("Restored path: %s\n", getenv("PATH"));
}
