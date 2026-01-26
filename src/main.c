/**
This is the SUSHI Shell - Strathclyde Unix-type SHell Implementation

⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣤⣤⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⣠⣴⣾⣿⡿⠿⠛⠛⠛⠛⠛⠛⠛⠻⠿⢿⣿⣶⣤⣄⠀⠀
⢠⣾⡿⠛⠉⠀⠀⠀⠀⣀⣀⣀⣀⣀⣀⠀⠀⠀⠀⠉⠛⢿⣷⡀
⣿⣿⠀⠀⠀⠀⠀⢶⣿⣿⣿⣿⣿⣿⣿⣿⡶⠀⠀⠀⠀⠈⣿⣷
⣿⣿⣷⣄⡀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⢀⣠⣾⣿⣿
⣿⣿⣿⣿⣿⣿⣶⣦⣤⣤⣤⣄⣠⣤⣤⣤⣴⣶⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⡿⠛⢿⣿⣿⣿⣿⡿⠛⢿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣦⣾⣿⣿⣿⣿⣷⣴⣿⣿⣿⣿⣿⣿⣿⣿
⢻⣿⣿⣿⣿⣿⣿⣏⠀⠉⠛⠛⠛⠛⠉⠀⣹⣿⣿⣿⣿⣿⣿⡟
⠀⠻⣿⣿⣿⣿⣿⣿⣿⣶⣦⣤⣤⣴⣶⣿⣿⣿⣿⣿⣿⣿⠟⠀
⠀⠀⠈⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠋⠁⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠉⠉⠙⠛⠛⠛⠛⠋⠉⠉⠀⠀⠀⠀⠀⠀⠀
**/

#include "../include/externelRunner.h"
#include "../include/input.h"

int main(void) {
  char input[INPUT_LEN] = "\0";

  while (get_input(input)) {
    printf("Santized: \"%s\"\n", input);
    input[0] = '\0';
  }
}
