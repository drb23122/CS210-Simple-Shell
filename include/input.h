#define INPUT_LEN 512

#define BLINK "\x1b[5m"
#define RESET "\x1b[0m"

#define PURPLE_FG "\x1b[38:5:163m"
#define ORANGE_FG "\x1b[38:5:202m"
#define BLUE_FG "\x1b[38:5:51m"
#define BLACK_FG "\x1b[30m"

#define PURPLE_BG "\x1b[48:5:163m"
#define ORANGE_BG "\x1b[48:5:202m"
#define BLUE_BG "\x1b[48:5:51m"
#define BLACK_BG "\x1b[49m"

// Read in input from stdin
int get_input(char *input_buffer, char *output[INPUT_LEN]);

// Turn input string into array of strings in output
int tokenize(char input[INPUT_LEN], char *output[INPUT_LEN]);

// Delete all words in array
int clear(char *array[INPUT_LEN]);

// Print all tokens in array
void print_tokens(char *tokens[INPUT_LEN]);

void stop_flashing_cursor(char *tokens[INPUT_LEN]);
