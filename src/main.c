#include <stdio.h>
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

// ====
// MAIN
// ====

// The main entry point of the application
int main()
{

    char buffer[1024]; // Buffer to store the data coming in from stdin
    char *text;        // The text to write to the console

    // Read the contents from the stdin
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        text = buffer;
    }
    else
    {
        fprintf(stderr, "Error reading input\n");
        return 1; // Exit code 1 for failure
    }

    // Write it to the console like a typewriter
    typewriter(text);

    return 0; // Exit code 0 for success
}
