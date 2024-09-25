#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "typewriter.h"
#include "cli.h"
#include "helpers.h"

// ====
// MAIN
// ====

// The main entry point of the application
int main(int argc, char *argv[])
{
    // `-h` and `--help`: Show help message
    if ((argc >= 2) && contains(argv[1], "-h"))
    {
        print_help();
        return 0;
    }
    if ((argc >= 2) && contains(argv[1], "--help"))
    {
        type_help();
        return 0;
    }

    // `-V`, `--version`: Show version number
    if ((argc >= 2) && (contains(argv[1], "-V") || contains(argv[1], "--version")))
    {
        print_version();
        return 0;
    }

    // Initialize the TypeWriter Configuration
    TypeWriterConfig config = {
        .cpm = 500,
        .variance = 250,
        .pauseMultiplier = 3.0,
    };

    // Parse the command-line arguments
    int result = parse_arguments(argc, argv, &config);
    if (result != -1)
    {
        return result;
    }

    char *text = "";

    // Check if input is interactive (from a terminal) or redirected (from a file descriptor like STDIN)
    if (!is_interactive(stdin))
    {
        // Read the text from standard input (STDIN)
        text = read_stdin();
        if (!text)
        {
            fprintf(stderr, "Error: Failed to read from STDIN\n");
            free(text);
            return EXIT_FAILURE;
        }
    }
    else
    {
        // Read text from the terminal interactively
        printf("Enter text: ");
        text = read_stdin_interactively();
        if (!text)
        {
            fprintf(stderr, "Error: Failed to read from STDIN interactively\n");
            free(text);
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
            typewriter(text, &config);
            printf("\n");

            // If a keypress is detected, then exit immediately
            if (key_pressed())
            {
                get_pressed_key(); // Consume the key so that it doesn't bleed out
                break;
            }

        } while (config.loop);

        exit_alt_buffer();
    }
    else
    {
        // ... Otherwise, run the typewriter once
        typewriter(text, &config);
    }

// Reset terminal setup for key capture on non-windows os
#ifndef _WIN32
    reset_terminal_mode();
#endif

    // Free the allocated memory
    if (!is_interactive(stdin))
    {
        free(text);
    }

    return 0; // Exit code 0 for success
}
