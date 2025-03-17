#ifndef PARTITION_ALGO
#define PARTITION_ALGO

#include <stdio.h>
#include <stdlib.h>

#include "../partition.h"
#include "../partitions2json.h"

void algo(int **arr, Partitions *p, int nThreads, bool verbose, char *num);

bool* seq(Partitions *p, int **arr);
bool* mlt_stc(Partitions *p, int **arr);
bool* mlt_dyn(Partitions *p, int **arr);
bool* sgl_dyn(Partitions *p, int **arr);
bool* sgl_stc(Partitions *p, int **arr);
bool* nested(Partitions *p, int **arr);

#endif