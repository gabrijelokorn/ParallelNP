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

void echo(Partitions *p, bool *result, double elapsed, char *algo, char *num, bool verbose)
{
    if (!verbose)
        return;

    char *algoresult = generateFilename(algo, num, "json");
    writePartitions(result, p->rows, algoresult);

    char *algotime = generateFilename(algo, num, "txt");
    writeTime(elapsed, algotime);
}

bool *run_with_timeout(bool *(*func)(Partitions *, int **), Partitions *p, int **arr, char *name, char *num, int verbose)
{
    signal(SIGALRM, timeout_handler);
    alarm(25); 

    double start = omp_get_wtime();
    bool *result = func(p, arr);
    double end = omp_get_wtime();

    alarm(0); 
    echo(p, result, end - start, name, num, verbose);
}

void algo(Partitions *p, int **arr, char *num, bool verbose)
{
    run_with_timeout(seq, p, arr, "seq", num, verbose);
    run_with_timeout(mlt_stc, p, arr, "mlt_stc", num, verbose);
    run_with_timeout(mlt_dyn, p, arr, "mlt_dyn", num, verbose);
    run_with_timeout(sgl_dyn, p, arr, "sgl_dyn", num, verbose);
    run_with_timeout(sgl_stc, p, arr, "sgl_stc", num, verbose);
    run_with_timeout(nested, p, arr, "nested", num, verbose);

    return;
}
