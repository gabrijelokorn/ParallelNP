#include <stdbool.h>
#include <omp.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "../../common/parallelNP.h"
#include "algo.h"

bool *run_algo(int **arr,  Partitions *p, bool *(*func)(Partitions *, int **), char *name, char *num)
{
    double start = omp_get_wtime();
    bool *result = func(p, arr);
    double end = omp_get_wtime();
    
    alarm(0); 

    char *algoresult = generateFilename(name, num, "json");
    writePartitions(result, p->rows, algoresult);
    
    char *algotime = generateFilename(name, num, "txt");
    writeTime(end - start, algotime);
}

void algo(int **arr, Partitions *p, char *num)
{
    run_algo(arr, p, seq, "seq", num);
    run_algo(arr, p, mlt_stc, "mlt_stc", num);
    run_algo(arr, p, mlt_dyn, "mlt_dyn", num);
    run_algo(arr, p, sgl_dyn, "sgl_dyn", num);
    run_algo(arr, p, sgl_stc, "sgl_stc", num);
    run_algo(arr, p, nested, "nested", num);

    return;
}
