#include <stdbool.h>

#include "../../common/parallelNP.h"
#include "small.h"

void small(int **arr, Partitions *p, bool verbose, char* outS, char* outP)
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
        FILE* fileS = openFile(outS, "w");
        writePartitions(fileS, resultS, p->rows);

        fclose(fileS);
    }

    return;
}
