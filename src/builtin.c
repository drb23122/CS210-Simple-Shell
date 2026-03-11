#include "../include/builtin.h"
#include "../include/alias.h"
#include "../include/env.h"
#include "../include/history.h"
#include "../include/input.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// get rid of unused argument warnings
// since all builtin functions must have same arguments and return types
#define UNUSED(x) (void)(x)

const int num = 6;
const char *names[] = {"getpath", "setpath", "cd",
                       "history", "alias",   "aliases"};
int (*funcs[])(char **) = {&getpath,       &setpath, &cd,
                           &print_history, &alias,   &print_aliases};

int check_builtin(char *tokens[INPUT_LEN]) {
  if (!tokens[0]) {
    return 1;
  }
  for (int i = 0; i < num; i++) {
    if (!strcmp(tokens[0], names[i])) {
      funcs[i](tokens);
      return 1;
    }
  }
  return 0;
}

int getpath(char *tokens[INPUT_LEN]) {
  if (tokens[1]) {
    printf("getpath doesn't take any arguments!\n");
    return 1;
  }
  printf("%s\n", getenv("PATH"));
  return 0;
}

int setpath(char *tokens[INPUT_LEN]) {
  if (!tokens[1]) {
    printf("Please provide a path!\n");
    return 1;
  }
  return setenv("PATH", tokens[1], 1);
}

int cd(char *tokens[INPUT_LEN]) {
  if (!tokens[1]) {
    set_home();
    return 0;
  }
  if (tokens[2]) {
    printf("cd takes only one argument!\n");
    return 1;
  }
  if (chdir(tokens[1])) {
    fprintf(stderr, "cd: %s: %s\n", tokens[1], strerror(errno));
    return 1;
  }
  return 0;
}

int print_history(char *tokens[INPUT_LEN]) {
  // check if second token exists..don't print history
  if (tokens[1]) {
    printf("History doesn't take parameters!\n");
    return 1; // error code
  }

  UNUSED(tokens);
  output_hist(stdout);
  return 0;
}

int alias(char *tokens[INPUT_LEN]) {
  add_alias(tokens);
  return 0;
}

int print_aliases(char *tokens[INPUT_LEN]) {
  UNUSED(tokens);
  output_aliases(stdout);
  return 0;
}
