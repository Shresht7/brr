#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h> // For Sleep function on Windows
#else
#include <unistd.h> // For usleep function on UNIX based systems
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

/// @brief Returns a random number between the given range
/// @param lower The lower bound
/// @param upper The upper bound
/// @return A random number between lower and upper.
int get_random_number_between(int lower, int upper)
{
    if (lower > upper)
    {
        // Swap lower and upper bounds
        int temp = lower;
        lower = upper;
        upper = temp;
    }
    return (rand() % (upper - lower + 1)) + lower;
}

/// @brief Determines if a character should cause a pause
/// @param cfg The TypeWriterConfig containing pause characters
/// @param c The character to check
/// @return The pause multiplier if the character should cause a pause, otherwise 1.0
float get_pause_multiplier(const TypeWriterConfig *cfg, char c)
{
    for (int i = 0; i < cfg->pauseCharCount; i++)
    {
        if (cfg->pauseChars[i].character == c)
        {
            return cfg->pauseChars[i].multiplier;
        }
    }
    return 1.0;
}
/// @brief Platform Independent Sleep
/// @param duration The duration in milliseconds to sleep for
void sleep(int duration)
{
#ifdef _WIN32
    Sleep(duration);
#else
    usleep(duration * 1000);
#endif
}

/// @brief Writes the given text like a typewriter
/// @param text The text to write to the screen
void typewriter(const TypeWriterConfig *cfg)
{
    srand(time(NULL)); // Seed the random number generator

    int speed_lower_bound = cfg->cpm - cfg->variance;
    int speed_upper_bound = cfg->cpm + cfg->variance;

    /// If 1, we are currently in an ANSI escape sequence
    int in_escape_sequence = 0;

    size_t len = strlen(cfg->text);
    for (int i = 0; i < len; i++)
    {
        printf("%c", cfg->text[i]);
        fflush(stdout); // Ensure the character is printed immediately

        // Check if the character is the start of an ANSI escape sequence
        if (cfg->text[i] == '\x1b' && cfg->text[i + 1] == '[')
        {
            in_escape_sequence = 1;
            continue; // Skip the delay
        }

        if (in_escape_sequence)
        {
            if (isalpha(cfg->text[i]))
            {
                in_escape_sequence = 0; // End of the ANSI escape sequence
            }
            continue; // Skip the delay
        }

        // Delay the next character
        if (isprint((unsigned char)cfg->text[i]))
        {
            int speed = get_random_number_between(speed_lower_bound, speed_upper_bound);
            int pauseFor = (60 * 1000) / speed;
            pauseFor *= get_pause_multiplier(cfg, cfg->text[i]);
            sleep(pauseFor);
        }
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
