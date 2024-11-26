#include <stdbool.h>

#include "../../common/parallelNP.h"
#include "large.h"

void large(int **arr, Partitions *p, bool verbose, char* outS, char* outP)
{
    // Sequential
    bool resultS = seq(arr[0], p->cols[0]);

    // Write the results to the file
    if (verbose)
    {
        FILE* fileS = openFile(outS, "w");
        writePartitions(fileS, &resultS, 1);

        fclose(fileS);
    }

    return;
}
