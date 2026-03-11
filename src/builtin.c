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

const int NUM = 6;
const char *names[] = {"getpath", "setpath", "cd",
                       "history", "alias",   "aliases"};
void (*const funcs[])(char **) = {&getpath,       &setpath, &cd,
                                  &print_history, &alias,   &print_aliases};

int check_builtin(char *tokens[INPUT_LEN]) {
  if (!tokens[0]) {
    return 1;
  }
  for (int i = 0; i < NUM; i++) {
    if (!strcmp(tokens[0], names[i])) {
      funcs[i](tokens);
      return 1;
    }
  }
  return 0;
}

void getpath(char *tokens[INPUT_LEN]) {
  if (tokens[1]) {
    printf("getpath doesn't take any arguments!\n");
  } else {
    printf("%s\n", getenv("PATH"));
  }
}

void setpath(char *tokens[INPUT_LEN]) {
  if (!tokens[1]) {
    printf("Please provide a path!\n");
  } else {
    setenv("PATH", tokens[1], 1);
  }
}

void cd(char *tokens[INPUT_LEN]) {
  if (!tokens[1]) {
    set_home();
  } else if (tokens[2]) {
    printf("cd takes only one argument!\n");
  } else if (chdir(tokens[1])) {
    // error occured in changing directory, so print error and directory
    fprintf(stderr, "cd: %s: %s\n", tokens[1], strerror(errno));
  }
}

void print_history(char *tokens[INPUT_LEN]) {
  // check if second token exists..don't print history
  if (tokens[1]) {
    printf("history doesn't take parameters!\n");
  } else {
    output_hist(stdout);
  }
}

void alias(char *tokens[INPUT_LEN]) {
  if (!add_alias(tokens)) {
    printf("Alias %s saved!\n", tokens[1]); // no error occured
  }
}

void print_aliases(char *tokens[INPUT_LEN]) {
  if (tokens[1]) {
    printf("aliases doesn't take parameters!\n");
  } else {
    output_aliases(stdout);
  }
}
