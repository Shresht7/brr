#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct
{
    char *text; // The text to write
    int cpm;    // The Characters-Per-Minute speed
} TypeWriterConfig;

/// @brief Writes the given text like a typewriter
/// @param text The text to write to the screen
void typewriter(const TypeWriterConfig *cfg)
{
    int len = strlen(cfg->text);
    int pauseFor = (60 * 1000) / cfg->cpm;

    for (int i = 0; i < len; i++)
    {
        printf("%c", cfg->text[i]);
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
    // Initialize the TypeWriter Configuration
    TypeWriterConfig config = {
        .text = NULL,
        .cpm = 750,
    };

    // Read the text from STDIN
    config.text = read_stdin();

    // Write it to the console like a typewriter
    typewriter(&config);

    // Free the allocated memory
    free(config.text);

    return 0; // Exit code 0 for success
}
