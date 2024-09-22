#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// isatty is undefined in Windows. _isatty must be used from the io.h library
#ifdef _WIN32
#include <io.h>
#endif

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
        // If input is interactive (from a terminal), show an "Unsupported" message
        // TODO: Print the help message
        fprintf(stderr, "No Input");
        exit(1);
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

int is_interactive(FILE *stream)
{
#ifdef _WIN32
    return _isatty(_fileno(stream));
#else
    return isatty(_fileno(stream));
#endif
}
