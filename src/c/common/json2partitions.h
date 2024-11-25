#ifndef JSON2PARTITIONS_H
#define JSON2PARTITIONS_H

#include "./types.h"

dimensions *get_dimensions(char *buffer);
int **json2partitions(char *buffer, dimensions *d);

#endif