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
        .cpm = 750,
    };

    // Parse the command-line arguments
    int result = parse_arguments(argc, argv, &config);
    if (result != -1)
    {
        return result;
    }

    // Read the text from STDIN
    config.text = read_stdin();

    // Write it to the console like a typewriter
    typewriter(&config);

    // Free the allocated memory
    free(config.text);

    return 0; // Exit code 0 for success
}
