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
    char *text;         // The text to write
    int cpm;            // The Characters-Per-Minute speed
    int variance;       // The variance in the Characters-Per-Minute speed value
    int pauseCharCount; // The number of elements in the pauseChar array
    struct PauseChar
    {
        char character;   // Character to pause at
        float multiplier; // Multiplier for the pause duration
    } *pauseChars;        // Array of pause characters and their multipliers
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

        // Check if current character matches any pause character and adjust pauseFor accordingly
        for (int j = 0; j < cfg->pauseCharCount; j++)
        {
            if (cfg->text[i] == cfg->pauseChars[j].character)
            {
                pauseFor *= cfg->pauseChars[j].multiplier;
                break;
            }
        }

        printf("%c", cfg->text[i]);
        fflush(stdout); // Ensure the character is printed immediately

#ifdef _WIN32
        Sleep(pauseFor);
#else
        usleep(pauseFor * 1000);
#endif
    }
}

/// @brief Free dynamically allocated memory
/// @param config
void free_config(TypeWriterConfig *config)
{
    if (config->text)
    {
        free(config->text);
    }
}

int get_random_number_between(int lower, int upper)
{
    if (lower > upper)
    {
        fprintf(stderr, "Invalid bounds for random number generation\n");
        exit(EXIT_FAILURE);
    }
    return (rand() % (upper - lower + 1)) + lower;
}
