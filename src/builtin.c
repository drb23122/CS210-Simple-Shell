#include "../include/builtin.h"
#include "../include/alias.h"
#include "../include/env.h"
#include "../include/history.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define UNUSED(x) (void)(x)

const int num = 7;
const char *names[] = {"getpath", "setpath", "cd",     "history",
                       "alias",   "aliases", "unalias"};
int (*funcs[])(char **) = {&getpath, &setpath,       &cd,     &print_history,
                           &alias,   &print_aliases, &unalias};

int check_builtin(char *input[INPUT_LEN]) {
  if (!input[0]) {
    return 1;
  }
  for (int i = 0; i < num; i++) {
    if (!strcmp(input[0], names[i])) {
      funcs[i](input);
      return 1;
    }
  }
  return 0;
}

int getpath(char *input[INPUT_LEN]) {
  if (input[1]) {
    printf("getpath doesn't take any arguments!\n");
    return 1;
  }
  printf("%s\n", getenv("PATH"));
  return 0;
}

int setpath(char *input[INPUT_LEN]) {
  if (!input[1]) {
    printf("Please provide a path!\n");
    return 1;
  }
  return setenv("PATH", input[1], 1);
}

int cd(char *input[INPUT_LEN]) {
  if (!input[1]) {
    set_home();
    return 0;
  }
  if (input[2]) {
    printf("cd takes only one argument!\n");
    return 1;
  }
  if (chdir(input[1])) {
    perror("cd");
    return 1;
  }
  return 0;
}

int print_history(char *input[INPUT_LEN]) {
  UNUSED(input);
  output_hist(stdout);
  return 0;
}

int alias(char *input[INPUT_LEN]) {
  add_alias(input);
  printf("Alias %s saved!\n", input[1]);
  return 0;
}

int print_aliases(char *input[INPUT_LEN]) {
  UNUSED(input);
  output_aliases(stdout);
  return 0;
}

// This method exists to stop unlaias being executed since the unaliasing
// triggered by check_alias
int unalias(char *input[INPUT_LEN]) {
  UNUSED(input);
  return 0;
}
