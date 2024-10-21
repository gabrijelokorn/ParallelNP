# include <stdio.h>
#include "write.h"

void writeString(FILE *fp, char* str)
{
    fprintf(fp, "%s", str);
    return;
}
