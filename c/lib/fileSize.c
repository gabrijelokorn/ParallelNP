#include <stdio.h>
#include <stdlib.h>

#include "fileSize.h"

int getFileSize (FILE *fp)
{
    int size = 0;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    return size;
}