#ifndef CLI_H
#define CLI_H

int is_interactive(FILE *stream);

char *read_stdin();
char *read_stdin_interactively();

int parse_arguments(int argc, char *argv[], TypeWriterConfig *config);

#endif CLI_H
