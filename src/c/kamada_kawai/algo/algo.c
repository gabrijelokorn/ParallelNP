#include <stdbool.h>
#include <omp.h>
#include <time.h>

#include "algo.h"

void rewindVertices(KamadaKawai *kk, Vertices *result)
{
    for (int i = 0; i < kk->n; i++)
    {
        kk->coords[i].x = result->coords[i].x;
        kk->coords[i].y = result->coords[i].y;
    }
}

void echo(KamadaKawai *kk, Vertices *result, double elapsed, char *algo, char *num, bool verbose)
{
    if (!verbose)
        return;

    char *algoresult = parseFilename(algo, num, "csv");
    writeVertices(result, kk->n, algoresult);

    char *algotime = parseFilename(algo, num, "txt");
    writeTime(elapsed, algotime);
}

void algo(KamadaKawai *kk, char *num, bool verbose)
{
    double start;
    Vertices *result;
    double end;

    start = omp_get_wtime();
    result = seq(kk);
    end = omp_get_wtime();
    echo(kk, result, end - start, "seq", num, verbose);
    rewindVertices(kk, result);

    start = omp_get_wtime();
    result = par(kk);
    end = omp_get_wtime();
    echo(kk, result, end - start, "par", num, verbose);
    rewindVertices(kk, result);

    return;
}
