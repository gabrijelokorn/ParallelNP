#ifndef LARGE_H
#define LARGE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../partition.h"
#include "../partitions2json.h"

void large(int **arr, Partitions *p, bool verbose, char* outS, char* outP, char* outST, char* outPT);
bool large_seq(int *arr, int size);
bool large_par(int *arr, int size);

#endif