#include <stdbool.h>
#include <omp.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "../kamada_kawai.h"
#include "algo.h"

void timeout_handler(int signum)
{
    printf("Timeout reached!\n");
}

void rewindVertices(KamadaKawai *kk, Coord *original)
{
    for (int i = 0; i < kk->n; i++)
    {
        kk->coords[i].x = original[i].x;
        kk->coords[i].y = original[i].y;
    }
}

void run_with_timeout(KamadaKawai *kk, Vertices *(*func)(KamadaKawai *), int verbose, char *name, char *num)
{
    // signal(SIGALRM, timeout_handler);
    // alarm(25);

    double start = omp_get_wtime();
    Vertices *result = func(kk);
    double end = omp_get_wtime();

    // alarm(0);

    if (!verbose)
        return;
    char *algoresult = generateFilename(name, num, "csv");
    writeVertices(result, kk->n, algoresult);

    char *algotime = generateFilename(name, num, "txt");
    writeTime(end - start, algotime);

    return;
}

void algo(KamadaKawai *kk, bool verbose, char *num)
{
    Coord *original = malloc(kk->n * sizeof(Coord));
    copyCoords(kk->coords, original, kk->n);
    
    run_with_timeout(kk, seq, verbose, "seq", num);
    rewindVertices(kk, original);
    
    run_with_timeout(kk, par, verbose, "par", num);
    rewindVertices(kk, original);

    free(original);

    return;
}
