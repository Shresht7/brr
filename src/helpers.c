#include <string.h>

#ifdef _WIN32
#include <windows.h> // For Sleep function on Windows
#else
#include <unistd.h> // For usleep function on UNIX based systems
#endif

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

/// @brief Returns true if the input contains the given string
/// @return a boolean indicating if the input contains the given string
int contains(char *input, char *str)
{
    return strcmp(input, str) == 0;
}

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
