#include <stdio.h>
#include <string.h>
#include <time.h>

// ------------------------
// TYPEWRITER CONFIGURATION
// ------------------------

typedef struct
{
    int cpm;               // The Characters-Per-Minute speed
    int variance;          // The variance in the Characters-Per-Minute speed value
    float pauseMultiplier; // The ratio by which to increase the pause delay
    int loop;              // Should loop indefinitely until closed
} TypeWriterConfig;

// ---------
// EXECUTION
// ---------

/// @brief Writes the given text like a typewriter
/// @param text The text to write to the screen
void typewriter(char *text, const TypeWriterConfig *cfg)
{
    srand(time(NULL)); // Seed the random number generator

    int speed_lower_bound = cfg->cpm - cfg->variance;
    int speed_upper_bound = cfg->cpm + cfg->variance;

    /// If 1, we are currently in an ANSI escape sequence
    int in_escape_sequence = 0;

    /// Keep track of the previously printed character, and speed up typing if we are
    /// repeatedly printing the same character.
    char prev = ' ';

    size_t len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        // If a keypress is detected, then exit immediately
        if (key_pressed())
        {
            return;
        }

        printf("%c", text[i]);
        fflush(stdout); // Ensure the character is printed immediately

        // Check if the character is the start of an ANSI escape sequence
        if (text[i] == '\x1b' && text[i + 1] == '[')
        {
            in_escape_sequence = 1;
            continue; // Skip the delay
        }

        if (in_escape_sequence)
        {
            if (isalpha(text[i]))
            {
                in_escape_sequence = 0; // End of the ANSI escape sequence
            }
            continue; // Skip the delay
        }

        // If this is an non-printable character, skip the delay and continue iterating
        if (!isprint((unsigned char)text[i]))
        {
            continue;
        }

        // Delay the next character
        int speed = get_random_number_between(speed_lower_bound, speed_upper_bound);
        int pauseFor = (60 * 1000) / speed;
        // Apply multiplier if the character is not a lowercase alphabet
        if ((text[i] != ' ') && (text[i] < 'a' || text[i] > 'z'))
        {
            pauseFor *= cfg->pauseMultiplier;
        }

        // If we are repeating the same character multiple times, reduce the delay
        if (text[i] == prev)
        {
            pauseFor /= 2;
        }
        else
        {
            prev = text[i];
        }

        sleep(pauseFor);
    }
}
