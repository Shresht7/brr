#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "typewriter.h"
#include "cli.h"

// ====
// MAIN
// ====

// The main entry point of the application
int main(int argc, char *argv[])
{
    // Initialize the TypeWriter Configuration
    TypeWriterConfig config = {
        .text = NULL,
        .cpm = 500,
        .variance = 250,
    };

    // Parse the command-line arguments
    int result = parse_arguments(argc, argv, &config);
    if (result != -1)
    {
        return result;
    }

    // Check if input is interactive (from a terminal) or redirected (from a file descriptor like STDIN)
    if (!is_interactive(stdin))
    {
        // Read the text from standard input (STDIN)
        config.text = read_stdin();
    }
    else
    {
        printf("Enter text: ");
        config.text = read_stdin_interactively();
    }

    // Write it to the console like a typewriter
    typewriter(&config);

    // Free the allocated memory
    if (!is_interactive(stdin))
    {
        free(config.text);
    }

    return 0; // Exit code 0 for success
}
