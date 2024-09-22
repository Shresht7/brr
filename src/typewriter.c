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
    char *text;   // The text to write
    int cpm;      // The Characters-Per-Minute speed
    int variance; // The variance in the Characters-Per-Minute speed value
} TypeWriterConfig;

// ---------
// EXECUTION
// ---------

/// @brief Writes the given text like a typewriter
/// @param text The text to write to the screen
void typewriter(const TypeWriterConfig *cfg)
{
    srand(time(NULL)); // Seed the random number generator

    int speed_lower_bound = cfg->cpm - cfg->variance;
    int speed_upper_bound = cfg->cpm + cfg->variance;

    size_t len = strlen(cfg->text);
    for (int i = 0; i < len; i++)
    {
        int speed = get_random_number_between(speed_lower_bound, speed_upper_bound);
        int pauseFor = (60 * 1000) / speed;
        printf("%c", cfg->text[i]);

#ifdef _WIN32
        Sleep(pauseFor);
#else
        usleep(pauseFor * 1000);
#endif
    }
}

int get_random_number_between(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}
