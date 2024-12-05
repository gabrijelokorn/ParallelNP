#ifndef SMALL_H
#define SMALL_H

#include <stdio.h>
#include <stdlib.h>

#include "../partition.h"
#include "../partitions2json.h"

void small(int **arr, Partitions *p, bool verbose, char* outS, char* outP);
bool* small_seq(int **arr, Partitions *p);
bool* small_par(int **arr, Partitions *p);

#endif