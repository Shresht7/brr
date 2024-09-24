#ifndef CLI_H
#define CLI_H

int is_interactive(FILE *stream);

char *read_stdin();
char *read_stdin_interactively();

int parse_arguments(int argc, char *argv[], TypeWriterConfig *config);

void print_version();
void print_help();

void enter_alt_buffer();
void exit_alt_buffer();
void clear_screen();
void move_cursor_to_home();

#endif CLI_H
