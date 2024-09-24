#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// isatty is undefined in Windows. _isatty must be used from the io.h library
#ifdef _WIN32
#include <io.h>
#endif

#include "typewriter.h"
#include "helpers.h"

// ================
// STDIN / TERMINAL
// ================

/// @brief Returns a boolean indicating whether this is an interactive terminal session or not
/// @param stream The file descriptor to check
/// @return 1 if this is an interactive terminal or 0 if it is a redirected file
int is_interactive(FILE *stream)
{
#ifdef _WIN32
    return _isatty(_fileno(stream));
#else
    return isatty(_fileno(stream));
#endif
}

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

/// @brief Prompt the user for input and read the contents
/// @return A string input by the user
char *read_stdin_interactively()
{
    char buffer[1024];
    char *text;

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        strcpy_s(text, sizeof(buffer), buffer);
        // Remove newline character if present
        size_t len = strlen(text);
        if (len > 0 && text[len - 1] == '\n')
        {
            text[len - 1] = '\0';
        }
    }
    else
    {
        fprintf(stderr, "Error reading input\n");
        exit(1);
    }

    return text;
}

// ===============
// ARGUMENT PARSER
// ===============

/// @brief Parse the command-line arguments
/// @param argc The total count of arguments passed in
/// @param argv The vector containing the arguments
/// @param cfg The TypeWriter Configuration object to update
/// @return 1 if there was an error or -1 if there was no error
int parse_arguments(int argc, char *argv[], TypeWriterConfig *cfg)
{
    for (int i = 0; i < argc; i++)
    {
        if ((contains(argv[i], "-c")) || (contains(argv[i], "--cpm")))
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
        else if ((contains(argv[i], "-v") || contains(argv[i], "--variance")))
        {
            if (i + 1 < argc)
            {
                cfg->variance = atoi(argv[++i]);
            }
            else
            {
                fprintf(stderr, "Error: -v/--variance option requires an argument");
                return 1;
            }
        }
        else if ((contains(argv[i], "-l") || contains(argv[i], "--loop")))
        {
            cfg->loop = 1;
        }
    }
    return -1;
}

// ------------
// HELP MESSAGE
// ------------

/// @brief Prints the version number
void print_version()
{
    printf("v0.1.0");
}

/// @brief Prints the help message
void print_help()
{
    printf("Usage: typwr [options]\n");
    printf("\n");
    printf("Options:\n");
    printf("\n");
    printf("  -c, --cpm <cpm>         Characters per minute (default: 500)\n");
    printf("  -v, --variance <ms>     The variance in the cpm speed (default: 250)\n");
    printf("  -l, --loop              Repeat typing the same content indefinitely (Press any key to quit)\n");
    printf("\n");
    printf("  -h, --help              Show this help message\n");
    printf("  -V, --version           Show the version number\n");
}

// ----
// ANSI
// ----

/// @brief Enter the Alternate Buffer Screen
void enter_alt_buffer()
{
    printf("\x1b[?1049h");
}

/// @brief Exit the Alternate Buffer Screen
void exit_alt_buffer()
{
    printf("\x1b[?1049l");
}

/// @brief Clear the screen
void clear_screen()
{
    printf("\x1b[2J");
}

/// @brief Move cursor to the top left
void move_cursor_to_home()
{
    printf("\x1b[H");
}
