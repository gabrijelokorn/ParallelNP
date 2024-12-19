#include "./write.h"
#include "./error.h"

void *writeTime(FILE *fp, double time) {
    if (fp == NULL) {
        error_file();
        return NULL;
    }

    fprintf(fp, "%lf\n", time);

    return NULL;
}