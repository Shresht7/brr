#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h> // For Sleep function on Windows
#include <conio.h>
#else
#include <unistd.h> // For usleep function on UNIX based systems
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#endif

/// @brief Platform Independent Sleep
/// @param duration The duration in milliseconds to sleep for
void delay(int duration)
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

#ifdef _WIN32
/// @brief Check if a key has been pressed
/// @return 1 if a key has been pressed, 0 otherwise
int key_pressed()
{
    return _kbhit();
}

/// @brief Get the pressed key
/// @return the pressed key
int get_pressed_key()
{
    return _getch();
}
#else
struct termios orig_termios;

void reset_terminal_mode()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void set_terminal_mode()
{
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    atexit(reset_terminal_mode);
}

int key_pressed()
{
    int bytes_available;
    ioctl(STDIN_FILENO, FIONREAD, &bytes_available);
    return bytes_available > 0;
}

int get_pressed_key()
{
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}
#endif
