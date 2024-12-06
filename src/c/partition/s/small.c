#include <stdbool.h>
#include <omp.h>
#include <time.h>

#include "../../common/parallelNP.h"
#include "small.h"

void small(int **arr, Partitions *p, bool verbose, char *outS, char *outP)
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

        FILE *fileP = openFile(outP, "w");
        writePartitions(fileP, resultP, p->rows);
        fclose(fileP);
        
        // Print the times
        printf("Sequential: %f seconds\n", end_seq - start_seq);
        printf("Parallel: %f seconds\n", end_par - start_par);
    }

    free(resultS);
    free(resultP);

    return;
}
