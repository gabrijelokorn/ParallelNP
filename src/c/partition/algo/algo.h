#ifndef PARTITION_ALGO
#define PARTITION_ALGO

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../partition.h"
#include "../partitions2json.h"

void algo(Partitions *p, char *test_id, int repetitions);

bool seq(Partitions *p);
bool sgl_stc(Partitions *p);

#endif