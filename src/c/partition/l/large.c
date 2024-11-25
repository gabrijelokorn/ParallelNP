#include <stdbool.h>

#include "large.h"

void large(int **arr, Partitions *p, bool verbose, FILE *outS, FILE *outP)
{
    // Sequential
    bool resultS = seq(arr[0], p->cols[0]);

    // Write the results to the file
    if (verbose)
    {
        writePartitions(outS, &resultS, 1);
    }

    return;
}
