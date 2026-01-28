#include "../include/builtin.h"
#include "../include/env.h"
#include "../include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int num = 3;
const char *names[] = {"getpath", "setpath", "cd"};
int (*funcs[])(char **) = {&getpath, &setpath, &cd};

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
