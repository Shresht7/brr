#ifndef TYPEWRITER_H
#define TYPEWRITER_H

typedef struct
{
    int cpm;
    int variance;
    double pauseMultiplier;
    int loop;
} TypeWriterConfig;

void typewriter(char *text, const TypeWriterConfig *config);

void free_config(TypeWriterConfig *config);

#endif // TYPEWRITER_H
