# include <stdio.h>
#include "write.h"

void writeString(char* filename, char* mode, char* str)
{
    FILE *file = fopen(filename, mode);
    fprintf(file, "%s", str);
    fclose(file);

    return;
}

void writeInt(char* filename, char* mode, int num)
{
    FILE *file = fopen(filename, mode);
    fprintf(file, "%d", num);
    fclose(file);

    return;
}
