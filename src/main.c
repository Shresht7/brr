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
    // `-h` and `--help`: Show help message
    if ((argc <= 1) || (contains(argv[1], "-h") || contains(argv[1], "--help")))
    {
        print_help();
        return 0;
    }

    // `-V`, `--version`: Show version number
    if ((argc <= 2) && (contains(argv[1], "-V") || contains(argv[1], "--version")))
    {
        print_version();
        return 0;
    }

    // Initialize the TypeWriter Configuration
    TypeWriterConfig config = {
        .text = NULL,
        .cpm = 500,
        .variance = 250,
        .pauseAt = "\n",
        .pauseMultiplier = 3.0,
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
