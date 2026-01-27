#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int run(char *input[INPUT_LEN]) {

  pid_t p = fork();

  if (p > 0) {
    // Parent proccess
    wait(NULL);

  } else if (!p) {
    // Child proccess
    execvp(input[0], input);
    // If this point reached, an error occured in exec
    perror("Error: ");
    exit(1);

  } else {
    printf("Forking failed\n");
  }

  return 0;
}
