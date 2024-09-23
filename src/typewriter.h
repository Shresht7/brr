#ifndef TYPEWRITER_H
#define TYPEWRITER_H

typedef struct
{
    char *text;
    int cpm;
    int variance;
    char *pauseAt;
    float pauseMultiplier;
} TypeWriterConfig;

void typewriter(const TypeWriterConfig *config);

void free_config(TypeWriterConfig *config);

#endif // TYPEWRITER_H
