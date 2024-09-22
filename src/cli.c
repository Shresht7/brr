#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "typewriter.h"

/// @brief Read the contents from `STDIN`
/// @return A string
char *read_stdin()
{
    size_t size = 1024; // Initial size of the memory allocation for the buffer
    size_t len = 0;     // The current size of the buffer

    // Instantiate a buffer and dynamically allocate memory for it
    char *buffer = malloc(size);
    if (!buffer)
    {
        fprintf(stderr, "Memory Allocation Error\n");
        exit(1);
    }

    // Iterate over the characters from stdin
    int c;
    while ((c = fgetc(stdin)) != EOF)
    {
        // If we are going to go over the allocated size ...
        if (len + 1 >= size)
        {
            // Resize the buffer and reallocate the memory
            size *= 2;
            buffer = realloc(buffer, size);
            if (!buffer)
            {
                fprintf(stderr, "Memory Allocation Error\n");
                exit(1);
            }
        }

        // Store the character in the buffer
        buffer[len++] = (char)c;
    }

    buffer[len] = '\0'; // Close out the buffer with a NULL character
    return buffer;
}

/// @brief Parse the command-line arguments
/// @param argc The total count of arguments passed in
/// @param argv The vector containing the arguments
/// @param cfg The TypeWriter Configuration object to update
/// @return Exit Status Code
int parse_arguments(int argc, char *argv[], TypeWriterConfig *cfg)
{
    for (int i = 0; i < argc; i++)
    {
        if ((strcmp(argv[i], "-c") == 0) || (strcmp(argv[i], "--cpm") == 0))
        {
            if (i + 1 < argc)
            {
                cfg->cpm = atoi(argv[++i]);
            }
            else
            {
                fprintf(stderr, "Error: -c/--cpm option requires an argument\n");
                return 1;
            }
        }
    }
    return 0; // Exit Code: Success
}
