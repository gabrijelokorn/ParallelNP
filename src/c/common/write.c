#include "./write.h"
#include "./error.h"
#include "./file.h"

void *writeTime(double time, char* timeFile) {
    FILE *file = openFile(timeFile, "w");

    if (file == NULL) {
        error_file();
        return NULL;
    }

    fprintf(file, "%lf\n", time);

    return NULL;
}