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
  printf("%s", WEL);

  char *saved_path[2] = {NULL, save_path()}; // stored in form of input array
  printf("Saved path: %s\n", saved_path[1]);

  char cwd[100];
  getcwd(cwd, 100);
  printf("Old HOME: %s\n", cwd);
  set_home();
  getcwd(cwd, 100);
  printf("New HOME: %s\n", cwd);

  load_hist();
  load_aliases();

  char input_buffer[INPUT_LEN]; // Buffer for user input
  char *tokens[INPUT_LEN];      // Pointers to each token in buffer
  clear(tokens); // Clears data left over from previous run which causes errors

  while (get_input(input_buffer, tokens)) {
    if (!check_alias(tokens)) {
      if (!check_history(tokens)) {
        if (!check_builtin(tokens)) {
          run(tokens);
        }
      }
    }

    clear(tokens);
  }
  // Cleaning up
  setpath(saved_path);
  free(saved_path[1]);
  printf("Restored path: %s\n", getenv("PATH"));

  save_hist();
  save_aliases();
  free_hist();

  printf("%s", EXI);
}
