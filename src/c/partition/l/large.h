#ifndef LARGE_H
#define LARGE_H

#include <stdio.h>
#include <stdlib.h>

#include "../types.h"
#include "../partitions2json.h"

void large(int **arr, Partitions *p, bool verbose, char* outS, char* outP);
bool seq(int *arr, int size);

#endif