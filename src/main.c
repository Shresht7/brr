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
    // TODO: Move this to a different file and add other characters like brackets etc. Anything other than lowercase alphabets should cause slowdowns
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
        // Read text from the terminal interactively
        printf("Enter text: ");
        config.text = read_stdin_interactively();
        if (!config.text)
        {
            fprintf(stderr, "Error: Failed to read from STDIN interactively\n");
            free_config(&config);
            return EXIT_FAILURE;
        }
    }

// Setup key-capture on non-windows os
#ifndef _WIN32
    set_terminal_mode();
#endif

    // If we are to continuously loop ...
    if (config.loop)
    {
        // Switch to the alternate buffer for rendering
        enter_alt_buffer();
        clear_screen();
        move_cursor_to_home();

        do
        {
            // ...Run the typewriter
            typewriter(&config);
            printf("\n");

            // If a keypress is detected, then exit immediately
            if (key_pressed())
            {
                break;
            }

        } while (config.loop);

        exit_alt_buffer();
    }
    else
    {
        // ... Otherwise, run the typewriter once
        typewriter(&config);
    }

// Reset terminal setup for key capture on non-windows os
#ifndef _WIN32
    reset_terminal_mode();
#endif

    // Free the allocated memory
    if (!is_interactive(stdin))
    {
        free_config(&config);
    }

    return 0; // Exit code 0 for success
}
