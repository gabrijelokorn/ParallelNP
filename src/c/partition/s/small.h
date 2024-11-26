#ifndef SMALL_H
#define SMALL_H

#include <stdio.h>
#include <stdlib.h>

#include "../types.h"
#include "../partitions2json.h"

void small(int **arr, Partitions *p, bool verbose, char* outS, char* outP);
bool seq(int *arr, int size);

#endif