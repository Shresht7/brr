#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/// @brief Writes the given text like a typewriter
/// @param text The text to write to the screen
void typewriter(const char *text)
{
    int pauseFor = 100;
    while (*text)
    {
        printf("%c", *text);
        text++;
        usleep(pauseFor * 1000);
    }
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

// ====
// MAIN
// ====

// The main entry point of the application
int main()
{

    // Read the text from STDIN
    char *text = read_stdin();

    // Write it to the console like a typewriter
    typewriter(text);

    // Free the allocated memory
    free(text);

    return 0; // Exit code 0 for success
}
