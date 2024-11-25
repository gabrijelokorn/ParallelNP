#ifndef JSON2PARTITIONS_H
#define JSON2PARTITIONS_H

#include "./types.h"

Partitions *get_partitions(char *buffer);
int **json2partitions(char *buffer, Partitions *d);

#endif