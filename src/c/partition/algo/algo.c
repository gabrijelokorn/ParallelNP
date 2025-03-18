#include <stdbool.h>
#include <omp.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "../../common/parallelNP.h"
#include "algo.h"

void timeout_handler(int signum)
{
    printf("Timeout reached!\n");
    exit(0);
}

bool *run_with_timeout(int **arr,  Partitions *p, bool *(*func)(Partitions *, int **), int verbose, char *name, char *num)
{
    signal(SIGALRM, timeout_handler);
    alarm(25); 
    
    double start = omp_get_wtime();
    bool *result = func(p, arr);
    double end = omp_get_wtime();
    
    alarm(0); 

    if (!verbose)
        return NULL;
    char *algoresult = generateFilename(name, num, "json");
    writePartitions(result, p->rows, algoresult);
    
    char *algotime = generateFilename(name, num, "txt");
    writeTime(end - start, algotime);
}

void algo(int **arr, Partitions *p, bool verbose, char *num)
{
    run_with_timeout(arr, p, seq, verbose, "seq", num);
    run_with_timeout(arr, p, mlt_stc, verbose, "mlt_stc", num);
    run_with_timeout(arr, p, mlt_dyn, verbose, "mlt_dyn", num);
    run_with_timeout(arr, p, sgl_dyn, verbose, "sgl_dyn", num);
    run_with_timeout(arr, p, sgl_stc, verbose, "sgl_stc", num);
    run_with_timeout(arr, p, nested, verbose, "nested", num);

    return;
}
