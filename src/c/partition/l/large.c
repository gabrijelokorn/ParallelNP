#include <stdbool.h>
#include <omp.h>
#include <time.h>

#include "../../common/parallelNP.h"
#include "large.h"

void large(int **arr, Partitions *p, bool verbose, char *outS, char *outP, char *outST, char *outPT)
{
    // Sequential
    double start_seq = omp_get_wtime();
    bool resultS = large_seq(arr[0], p->cols[0]);
    double end_seq = omp_get_wtime();

    // Parallel
    double start_par = omp_get_wtime();
    bool resultP = large_par(arr[0], p->cols[0]);
    double end_par = omp_get_wtime();

    // Write the results to the file
    if (verbose)
    {
        FILE *fileS = openFile(outS, "w");
        writePartitions(fileS, &resultS, 1);
        fclose(fileS);
        FILE *timeS = openFile(outST, "w");
        writeTime(timeS, end_seq - start_seq);
        fclose(timeS);

        FILE *fileP = openFile(outP, "w");
        writePartitions(fileP, &resultP, 1);
        fclose(fileP);
        FILE *timeP = openFile(outPT, "w");
        writeTime(timeP, end_par - start_par);
        fclose(timeP);
    }

    return;
}
