#include <stdio.h>
#include <stdlib.h>

#include "file.h"

char *generateFilename(char *algo, char *num, char *ext)
{
    char *filename = (char *)malloc(100 * sizeof(char));
    sprintf(filename, "algo/%s%s.%s", algo, num, ext);
    
    return filename;
}

FILE *openFile(char *filename, char *mode)
{
    FILE *fp = fopen(filename, mode);
    if (fp == NULL)
    {
        fprintf(stderr, "%s )-: File pointer is null\n", "openFile");
        return NULL;
    }

    return fp;
}