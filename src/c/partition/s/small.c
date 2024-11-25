#include <stdbool.h>

#include "small.h"

void small(int **arr, Partitions *p, bool verbose, FILE *outS, FILE *outP)
{
    // Sequential
    bool *resultS = (bool *)malloc(p->rows * sizeof(bool));
    for (int i = 0; i < p->rows; i++)
    {
        resultS[i] = seq(arr[i], p->cols[i]);
    }

    // Parallel
    // bool *resultP = (bool *)malloc(p->rows * sizeof(bool));
    // for (int i = 0; i < p->rows; i++)
    // {
    //     resultP[i] = par(arr[i], p->cols[i]);
    // }

    // Write the results
    if (verbose)
    {
        writePartitions(outS, resultS, p->rows);
    }

    return;
}
