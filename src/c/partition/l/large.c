#include <stdbool.h>
#include <time.h>

#include "../../common/parallelNP.h"
#include "large.h"

void large(int **arr, Partitions *p, bool verbose, char* outS, char* outP)
{
    // Sequential
    clock_t start_seq = clock();
    bool resultS = seq(arr[0], p->cols[0]);
    clock_t end_seq = clock();

    // Parallel
    printf("### ### ### ### ###\n");
    clock_t start_par = clock();
    bool resultP = par(arr[0], p->cols[0]);
    clock_t end_par = clock();

    // Print the times
    printf("Sequential: %f\n", (double)(end_seq - start_seq) / CLOCKS_PER_SEC);
    printf("Parallel: %f\n", (double)(end_par - start_par) / CLOCKS_PER_SEC);

    // Write the results to the file
    if (verbose)
    {
        FILE* fileS = openFile(outS, "w");
        writePartitions(fileS, &resultS, 1);

        FILE* fileP = openFile(outP, "w");
        writePartitions(fileP, &resultP, 1);

        fclose(fileS);
    }

    return;
}
