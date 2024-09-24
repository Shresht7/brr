#include <stdio.h>
#include <string.h>
#include <time.h>

// ------------------------
// TYPEWRITER CONFIGURATION
// ------------------------

typedef struct
{
    char *text;            // The text to write
    int cpm;               // The Characters-Per-Minute speed
    int variance;          // The variance in the Characters-Per-Minute speed value
    float pauseMultiplier; // The ratio by which to increase the pause delay
    int loop;              // Should loop indefinitely until closed
} TypeWriterConfig;

/// @brief Free dynamically allocated memory
/// @param config
void free_config(TypeWriterConfig *config)
{
    if (config->text)
    {
        free(config->text);
    }
}

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

    /// If 1, we are currently in an ANSI escape sequence
    int in_escape_sequence = 0;

    size_t len = strlen(cfg->text);
    for (int i = 0; i < len; i++)
    {
        // If a keypress is detected, then exit immediately
        if (key_pressed())
        {
            return;
        }

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
            // Apply multiplier if the character is not a lowercase alphabet
            if ((cfg->text[i] != ' ') && (cfg->text[i] < 'a' || cfg->text[i] > 'z'))
            {
                pauseFor *= cfg->pauseMultiplier;
            }
            sleep(pauseFor);
        }
    }
}
