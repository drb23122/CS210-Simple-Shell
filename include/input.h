#define INPUT_LEN 512

#define BLINK "\x1b[5m"

#define ANSI_RESET "\x1b[0m"
#define ANSI_RED ANSI_RESET "\x1b[31m"
#define ANSI_GREEN ANSI_RESET "\x1b[32m"
#define ANSI_BLUE ANSI_RESET "\x1b[34m"
#define ANSI_MAGENTA ANSI_RESET "\x1b[35m"

#define ANSI_RED_BG ANSI_RESET "\x1b[41m"
#define ANSI_GREEN_BG ANSI_RESET "\x1b[42m"
#define ANSI_BLUE_BG ANSI_RESET "\x1b[44m"
#define ANSI_MAGENTA_BG ANSI_RESET "\x1b[45m"

#define RED_BG_BLACK_BG "\x1b[30;41m"
#define GREEN_FG_BLUE_BG "\x1b[32;44m"

// Read in input from stdin
int get_input(char *input_buffer, char *output[INPUT_LEN]);

// Turn input string into array of strings in output
int tokenize(char input[INPUT_LEN], char *output[INPUT_LEN]);

// Delete all words in array
int clear(char *array[INPUT_LEN]);

// Print all tokens in array
void print_tokens(char *array[INPUT_LEN]);
