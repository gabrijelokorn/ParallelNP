#include <stdbool.h>
#include <omp.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "../kamada_kawai.h"
#include "algo.h"

void run_algo(KamadaKawai *kk, void (*func)(KamadaKawai *), char *name, char *num)
{
    // --- SETUP --- //
    Coord *original = malloc(kk->n * sizeof(Coord));
    copyCoords(kk->coords, original, kk->n); // Copy the original data

    // --- EXECTUTION --- //
    double start = omp_get_wtime(); // Start algorithm time
    func(kk);                       // Run the algorithm
    double end = omp_get_wtime();   // End algoritYYYm time

    // --- WRITE RESULTS TO FILE --- //
    char *algoresult = generateFilename(name, num, "csv");
    FILE *fp = fopen(algoresult, "w");
    writeState(fp, original, kk->n);
    writeState(fp, kk->coords, kk->n);
    fclose(fp);
    // --- WRITE TIME TO FILE --- //
    char *algotime = generateFilename(name, num, "txt");
    writeTime(end - start, algotime);
    
    // --- RESET DATA --- //
    copyCoords(original, kk->coords, kk->n); // Copy the original data back
    free(original);                          // Free the original data

    return;
}

void algo(KamadaKawai *kk, char *num)
{
    run_algo(kk, sgl_seq, "sgl_seq", num);
    run_algo(kk, sgl_par, "sgl_par", num);
    run_algo(kk, mlt_seq, "mlt_seq", num);
    run_algo(kk, mlt_par, "mlt_par", num);

    return;
}
