#ifndef TYPEWRITER_H
#define TYPEWRITER_H

typedef struct
{
    char *text;
    int cpm;
    int variance;
    int pauseCharCount;
    struct PauseChar
    {
        char character;   // Character to pause at
        float multiplier; // Multiplier for the pause duration
    } *pauseChars;        // Array of pause characters and their multipliers
    int loop;
} TypeWriterConfig;

void typewriter(const TypeWriterConfig *config);

void free_config(TypeWriterConfig *config);

#endif // TYPEWRITER_H
