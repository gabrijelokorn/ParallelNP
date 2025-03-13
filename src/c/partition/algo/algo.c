#include <stdbool.h>
#include <omp.h>
#include <time.h>

#include "../../common/parallelNP.h"
#include "algo.h"

void echo(Partitions *p, bool *result, double elapsed, char *algo, char *num, bool verbose)
{
    if (!verbose)
        return;

    char *algoresult = generateFilename(algo, num, "json");
    writePartitions(result, p->rows, algoresult);

    char *algotime = generateFilename(algo, num, "txt");
    writeTime(elapsed, algotime);
}

void algo(Partitions *p, int **arr, char *num, bool verbose)
{
    double start;
    bool *result;
    double end;

    start = omp_get_wtime();
    result = seq(p, arr);
    end = omp_get_wtime();
    echo(p, result, end - start, "seq", num, verbose);
    
    start = omp_get_wtime();
    result = mlt_stc(p, arr);
    end = omp_get_wtime();
    echo(p, result, end - start, "mlt_stc", num, verbose);

    start = omp_get_wtime();
    result = mlt_dyn(p, arr);
    end = omp_get_wtime();
    echo(p, result, end - start, "mlt_dyn", num, verbose);

    start = omp_get_wtime();
    result = sgl_dyn(p, arr);
    end = omp_get_wtime();
    echo(p, result, end - start, "sgl_dyn", num, verbose);

    start = omp_get_wtime();
    result = sgl_stc(p, arr);
    end = omp_get_wtime();
    echo(p, result, end - start, "sgl_stc", num, verbose);

    return;
}
