#include <stdio.h>
#include <stdlib.h>

#include "file.h"

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