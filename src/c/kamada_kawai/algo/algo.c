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

void resetData(KamadaKawai *kk, Coord *original)
{
    for (int i = 0; i < kk->n; i++)
    {
        kk->coords[i].x = original[i].x;
        kk->coords[i].y = original[i].y;
    }

    return;
}

void run_algo(KamadaKawai *kk, void (*func)(KamadaKawai *, Vertices *), int verbose, char *name, char *num)
{
    // --- PREPARE DATA STRUCTURES --- //
    Vertices *result = (Vertices *)malloc(sizeof(Vertices)); // Allocate space for testcase data
    Vertices *result_head = result;

    result->coords = (Coord *)malloc(kk->n * sizeof(Coord));
    copyCoords(kk->coords, result->coords, kk->n); // Copy the testcase data

    // --- TIME AND RUN ALGO --- //
    double start = omp_get_wtime(); // Start algorithm time
    func(kk, result);               // Run the algorithm
    double end = omp_get_wtime();   // End algorithm time

    // --- GET RESULTS --- //
    result->next = (Vertices *)malloc(sizeof(Vertices)); // Allocate space for resulting data
    result->next->coords = (Coord *)malloc(kk->n * sizeof(Coord));
    copyCoords(kk->coords, result->next->coords, kk->n); // Copy the result of execution

    result = result->next;
    result->next = NULL; // Mark the last state

    // --- WRITE RESULTS TO FILES --- //
    if (!verbose)
        return;
    char *algoresult = generateFilename(name, num, "csv");
    writeVertices(result_head, kk->n, algoresult);
    char *algotime = generateFilename(name, num, "txt");
    writeTime(end - start, algotime);

    free(result);
    return;
}

void algo(KamadaKawai *kk, bool verbose, char *num)
{
    Coord *original = malloc(kk->n * sizeof(Coord));
    copyCoords(kk->coords, original, kk->n);

    run_algo(kk, seq, verbose, "seq", num);
    resetData(kk, original);

    run_algo(kk, par, verbose, "par", num);
    resetData(kk, original);

    free(original);

    return;
}
