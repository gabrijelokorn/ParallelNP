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
    exit(0);
}

void rewindVertices(KamadaKawai *kk, Coord *original)
{
    for (int i = 0; i < kk->n; i++)
    {
        kk->coords[i].x = original[i].x;
        kk->coords[i].y = original[i].y;
    }
}

void echo(KamadaKawai *kk, Vertices *result, double elapsed, char *algo, char *num, bool verbose)
{
    if (!verbose)
        return;

    char *algoresult = generateFilename(algo, num, "csv");
    writeVertices(result, kk->n, algoresult);

    char *algotime = generateFilename(algo, num, "txt");
    writeTime(elapsed, algotime);
}

Vertices *run_with_timeout(Vertices *(*func)(KamadaKawai *), KamadaKawai *kk, char *name, char* num, int verbose)
{
    signal(SIGALRM, timeout_handler);
    alarm(25); 

    double start = omp_get_wtime();
    Vertices *result = func(kk);
    double end = omp_get_wtime();

    alarm(0); 
    echo(kk, result, end - start, name, num, verbose);

    return result;
}

void algo(KamadaKawai *kk, char *num, bool verbose)
{
    Coord *original = malloc(kk->n * sizeof(Coord));
    copyCoords(kk->coords, original, kk->n);

    run_with_timeout(seq, kk, "seq", num, verbose);
    rewindVertices(kk, original);
    run_with_timeout(par, kk, "par", num, verbose);
    rewindVertices(kk, original);
    run_with_timeout(nested, kk, "nested", num, verbose);
    rewindVertices(kk, original);

    free(original);

    return;
}
