#ifndef JSON2ARRAY_H

#define JSON2ARRAY_H

#include <stdlib.h>
#include <json-c/json.h>

#include "./types.h"

dimensions *dims(char *buffer);
int **json2array(char *buffer, dimensions *d);

#endif