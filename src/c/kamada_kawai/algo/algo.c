#include <stdbool.h>
#include <omp.h>
#include <time.h>

#include "algo.h"

void rewindVertices(KamadaKawai *kamadaKawai, Vertices *result)
{
    for (int i = 0; i < kamadaKawai->n; i++)
    {
        kamadaKawai->coords[i].x = result->coords[i].x;
        kamadaKawai->coords[i].y = result->coords[i].y;
    }
}

void echo(KamadaKawai *kamadaKawai, Vertices *result, double elapsed, char *algo, char *testcase, bool verbose)
{
    if (!verbose)
        return;

    char *algoresult = parseFilename(algo, testcase, "csv");
    writeVertices(result, kamadaKawai->n, algoresult);

    char *algotime = parseFilename(algo, testcase, "txt");
    writeTime(elapsed, algotime);
}

void algo(KamadaKawai *kamadaKawai, char *testcase, bool verbose)
{
    double start;
    Vertices *result;
    double end;

    start = omp_get_wtime();
    result = seq(kamadaKawai);
    end = omp_get_wtime();
    echo(kamadaKawai, result, end - start, "seq", testcase, verbose);
    rewindVertices(kamadaKawai, result);

    start = omp_get_wtime();
    result = par(kamadaKawai);
    end = omp_get_wtime();
    echo(kamadaKawai, result, end - start, "par", testcase, verbose);
    rewindVertices(kamadaKawai, result);

    return;
}
