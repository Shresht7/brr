#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

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
    size_t len = strlen(cfg->text);
    int pauseFor = (60 * 1000) / cfg->cpm;

    for (int i = 0; i < len; i++)
    {
        printf("%c", cfg->text[i]);

#ifdef _WIN32
        Sleep(pauseFor * 1000);
#else
        usleep(pauseFor * 1000);
#endif
    }
}
