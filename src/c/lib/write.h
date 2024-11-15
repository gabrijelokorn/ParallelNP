# ifndef WRITE_H
# define WRITE_H

# include <stdlib.h>
# include <stdio.h>
# include <json-c/json.h>

# include "types.h"

void writeString(FILE *fp, char* str);
void writeVertices(FILE *fp, Vertices *vertices, int n);
void writeJsonObject(FILE *fp, json_object *jobj);
void writeJsonArray(FILE *fp, json_object *jobj);

# endif