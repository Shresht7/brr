#include <stdio.h>
#include <unistd.h>
#include <time.h>

void typewriter(const char *text)
{
    int pauseFor = 100;
    while (*text)
    {
        printf("%c", *text);
        text++;
        usleep(pauseFor * 1000);
    }
}

int main()
{
    char *text = "Hello World!";
    typewriter(text);
    return 0;
}
