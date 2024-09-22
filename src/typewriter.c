#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// ------------------------
// TYPEWRITER CONFIGURATION
// ------------------------

typedef struct
{
    char *text; // The text to write
    int cpm;    // The Characters-Per-Minute speed
} TypeWriterConfig;

// ---------
// EXECUTION
// ---------

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
