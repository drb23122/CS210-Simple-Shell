#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// input in correct form, time to run
int run(char *tokens[INPUT_LEN]) {
  if (!*tokens) {
    return 1;
  }

  pid_t p = fork();
  if (p > 0) {
    // Parent proccess
    wait(NULL);

  } else if (!p) {
    // Child proccess
    if (execvp(tokens[0], tokens) == -1) {
      // If this point reached, an error occured in exec

      perror(tokens[0]);
      exit(1);
    }

  } else {
    printf("Forking failed\n");
    return 1;
  }

  return 0;
}
