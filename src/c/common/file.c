#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "file.h"

char *generateFilename(char *algo, char *num, char *ext)
{
    int nThreads = omp_get_max_threads();
    char *filename = (char *)malloc(100 * sizeof(char));
    sprintf(filename, "algo/%d/%s%s.%s", nThreads, algo, num, ext);

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