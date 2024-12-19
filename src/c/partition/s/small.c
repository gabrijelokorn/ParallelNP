#include <stdbool.h>
#include <omp.h>
#include <time.h>

#include "../../common/parallelNP.h"
#include "small.h"

void small(int **arr, Partitions *p, bool verbose, char *outS, char *outP, char *outST, char *outPT)
{
    // Sequential
    double start_seq = omp_get_wtime();
    bool *resultS = small_seq(arr, p);
    double end_seq = omp_get_wtime();

    // Parallel
    double start_par = omp_get_wtime();
    bool *resultP = small_par(arr, p);
    double end_par = omp_get_wtime();

    // Write the results
    if (verbose)
    {
        FILE *fileS = openFile(outS, "w");
        writePartitions(fileS, resultS, p->rows);
        fclose(fileS);
        FILE *timeS = openFile(outST, "w");
        writeTime(timeS, end_seq - start_seq);
        fclose(timeS);

        FILE *fileP = openFile(outP, "w");
        writePartitions(fileP, resultP, p->rows);
        fclose(fileP);
        FILE *timeP = openFile(outPT, "w");
        writeTime(timeP, end_par - start_par);
        fclose(timeP);
    }

    free(resultS);
    free(resultP);

    return;
}
