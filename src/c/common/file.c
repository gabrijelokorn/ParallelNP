#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <errno.h>

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
    if (filename == NULL) {
        fprintf(stderr, "openFile: filename is NULL\n");
        return NULL;
    }
    
    FILE *fp = fopen(filename, mode);
    if (fp == NULL) {
        fprintf(stderr, "openFile: Cannot open '%s': %s\n", filename, strerror(errno));
        return NULL;
    }
    
    return fp;
}