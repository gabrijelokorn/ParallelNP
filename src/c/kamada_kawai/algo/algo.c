#include <stdbool.h>
#include <omp.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "../kamada_kawai.h"
#include "algo.h"

void output_algo(KamadaKawai *kk, Coord *original, double elapsed, char *name, char *test_id)
{
    // --- WRITE RESULTS TO FILE --- //
    char *algoresult = generateFilename(name, test_id, "csv");
    FILE *algoresult_fp = fopen(algoresult, "w");
    writeState(algoresult_fp, original, kk->n);
    writeState(algoresult_fp, kk->coords, kk->n);
    fclose(algoresult_fp);
    // --- WRITE TIME TO FILE --- //
    char *algotime = generateFilename(name, test_id, "txt");
    FILE *algotime_fp = fopen(algotime, "w");
    writeTime(algotime_fp, elapsed);
    fclose(algotime_fp);
}

void run_algo(KamadaKawai *kk, void (*func)(KamadaKawai *), char *name, char *test_id, char *repetitions)
{
    // --- SETUP --- //
    Coord *original = malloc(kk->n * sizeof(Coord));
    copyCoords(kk->coords, original, kk->n); // Copy the original data

    // --- EXECTUTION --- //
    double time = 0;
    for (int i = 0; i < atoi(repetitions); i++)
    {
        double start = omp_get_wtime(); // Start algorithm time
        func(kk);                       // Run the algorithm
        double end = omp_get_wtime();   // End algoritYYYm time
        time += end - start;
    }
    time = time / atoi(repetitions);

    output_algo(kk, original, time, name, test_id); // Write results to file

    // --- RESET DATA --- //
    copyCoords(original, kk->coords, kk->n); // Copy the original data back
    free(original);                          // Free the original data

    return;
}

void algo(KamadaKawai *kk, char *test_id, char *repetitions)
{
    run_algo(kk, sgl_seq, "sgl_seq", test_id, repetitions);
    run_algo(kk, sgl_par, "sgl_par", test_id, repetitions);
    // run_algo(kk, mlt_seq, "mlt_seq", test_id, repetitions);
    // run_algo(kk, mlt_par, "mlt_par", test_id, repetitions);

    return;
}
