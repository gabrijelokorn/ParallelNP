# ifndef WRITE_H
# define WRITE_H

# include <stdlib.h>

# include "types.h"

void writeString(FILE *fp, char* str);
void writeJsonArray(FILE *fp, bool *result, int n);

# endif