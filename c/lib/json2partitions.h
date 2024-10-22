#ifndef JSON2PARTITIONS_H

#define JSON2PARTITIONS_H

#include <stdlib.h>
#include <json-c/json.h>

#include "./types.h"

dimensions *dims(char *buffer);
int **json2partitions(char *buffer, dimensions *d);

#endif