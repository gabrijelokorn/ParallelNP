#ifndef JSON2PARTITIONS_H
#define JSON2PARTITIONS_H

#include "./types.h"

dimensions *dims(char *buffer);
int **json2partitions(char *buffer, dimensions *d);

#endif