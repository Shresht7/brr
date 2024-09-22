#ifndef TYPEWRITER_H
#define TYPEWRITER_H

typedef struct
{
    char *text;
    int cpm;
    int variance;
} TypeWriterConfig;

void typewriter(const TypeWriterConfig *config);

#endif // TYPEWRITER_H
