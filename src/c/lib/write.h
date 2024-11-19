# ifndef WRITE_H
# define WRITE_H

# include <stdlib.h>
# include <stdio.h>
# include <json-c/json.h>
# include <stdbool.h>

# include "types.h"

void writeString(char *filename, char* str);
void writeVertices(char *filename, Vertices *vertices, int n);
void writeJsonArray(char *filename, bool *result, int n);

# endif