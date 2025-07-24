#ifndef PARTITION_ALGO
#define PARTITION_ALGO

#include <stdio.h>
#include <stdlib.h>

#include "../partition.h"
#include "../partitions2json.h"

void algo(Partitions *p, char *test_id, int repetitions);

void seq(Partitions *p, bool *result);
void sgl_stc(Partitions *p, bool *result);

#endif