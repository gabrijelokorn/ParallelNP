#include <stdbool.h>
#include <omp.h>
#include <time.h>

#include "../../common/parallelNP.h"
#include "algo.h"

void echo(Partitions *p, bool *result, double elapsed, char *algo, char *testcase, bool verbose)
{
    if (!verbose)
        return;

    char *algoresult = parseFilename(algo, testcase, "json");
    writePartitions(result, p->rows, algoresult);

    char *algotime = parseFilename(algo, testcase, "txt");
    writeTime(elapsed, algotime);
}

void algo(Partitions *p, int **arr, char *testcase, bool verbose)
{
    double start;
    bool *result;
    double end;

    start = omp_get_wtime();
    result = seq(p, arr);
    end = omp_get_wtime();
    echo(p, result, end - start, "seq", testcase, verbose);
    
    start = omp_get_wtime();
    result = par(p, arr);
    end = omp_get_wtime();
    echo(p, result, end - start, "par", testcase, verbose);

    return;
}
