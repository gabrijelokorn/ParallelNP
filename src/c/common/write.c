#include "./write.h"
#include "./error.h"
#include "./file.h"

void *writeTime(FILE *fp, double time)
{
    if (fp == NULL)
    {
        error_file();
        return NULL;
    }
    fprintf(fp, "%.9f\n", time);
    return NULL;
}