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
    struct PauseChar pauseChars[] = {
        {'\n', 3.0},
        {' ', 1.5},
        {'.', 2.0},
        {',', 1.75},
    };
    TypeWriterConfig config = {
        .text = NULL,
        .cpm = 500,
        .variance = 250,
        .pauseCharCount = 4,
        .pauseChars = pauseChars,
    };

    // Parse the command-line arguments
    int result = parse_arguments(argc, argv, &config);
    if (result != -1)
    {
        free_config(&config);
        return result;
    }

    // Check if input is interactive (from a terminal) or redirected (from a file descriptor like STDIN)
    if (!is_interactive(stdin))
    {
        // Read the text from standard input (STDIN)
        config.text = read_stdin();
        if (!config.text)
        {
            fprintf(stderr, "Error: Failed to read from STDIN\n");
            free_config(&config);
            return EXIT_FAILURE;
        }
    }
    else
    {
        printf("Enter text: ");
        config.text = read_stdin_interactively();
        if (!config.text)
        {
            fprintf(stderr, "Error: Failed to read from STDIN interactively\n");
            free_config(&config);
            return EXIT_FAILURE;
        }
    }

    // Write it to the console like a typewriter
    typewriter(&config);

    // Free the allocated memory
    if (!is_interactive(stdin))
    {
        free_config(&config);
    }

    return 0; // Exit code 0 for success
}
