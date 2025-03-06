#ifndef PARTITION_ALGO
#define PARTITION_ALGO

#include <stdio.h>
#include <stdlib.h>

#include "../partition.h"
#include "../partitions2json.h"

void algo(Partitions *p, int **arr, char *testcase, bool verbose);
bool* seq(Partitions *p, int **arr);
bool* par(Partitions *p, int **arr);

#endif