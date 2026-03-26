#include "../include/alias.h"
#include "../include/ascii_art.h"
#include "../include/builtin.h"
#include "../include/env.h"
#include "../include/execute.h"
#include "../include/history.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  printf("%s", WEL); // prints welcome ASCII art

  char *saved_path[INPUT_LEN] = {NULL};
  saved_path[1] = save_path(); // store PATH in form expected by setpath
  printf("Saved path: %s\n", saved_path[1]);

  // moving working directory
  char cwd[100];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("Old HOME: %s\n", cwd);
  }
  set_home();
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("New HOME: %s\n", cwd);
  }

  // loading hitory and aliases stored in persistent storage
  load_hist();
  load_aliases();

  char input_buffer[INPUT_LEN]; // Buffer for user input
  char *tokens[INPUT_LEN];      // Pointers to each token in buffer
  clear(tokens); // Clears data left over from previous run which causes errors

  // run until termination command is entered
  while (get_input(input_buffer, tokens)) {
    char *original[INPUT_LEN] = {NULL};
    copy_tokens(tokens, original);

    // add only originally typed non-history commands to history
    if (tokens[0] && tokens[0][0] != '!') {
      history_add(original);
    }

    if (!check_history(tokens)) {
      // after history substitution, do alias expansion once
      if (!check_alias(tokens)) {
        if (!check_builtin(tokens)) {
          run(tokens);
        }
      }
    }

    free_token_copy(original);
    clear(tokens);
  }

  // Cleaning up
  setpath(saved_path);
  free(saved_path[1]);
  printf("Restored path: %s\n", getenv("PATH"));

  // save back to file
  save_hist();
  save_aliases();
  free_hist();

  // printing exit ASCII art
  printf("%s", EXI);
}
