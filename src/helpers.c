#include <string.h>

#ifdef _WIN32
#include <windows.h> // For Sleep function on Windows
#include <conio.h>
#else
#include <unistd.h> // For usleep function on UNIX based systems
#include <termios.h>
#include <sys/select.h>
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
/// @brief Set terminal mode to non-canonical and non-echo
void set_terminal_mode()
{
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

/// @brief Reset terminal mode to canonical and echo
void reset_terminal_mode()
{
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

/// @brief Check if a key has been pressed
/// @return 1 if a key has been pressed, 0 otherwise
int key_pressed()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

/// @brief Get the pressed key
/// @return the pressed key
int get_pressed_key()
{
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}
#endif
