#include <stdbool.h>
#include <omp.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "../../common/parallelNP.h"
#include "algo.h"

void output_algo(Partitions *p, bool *result, double avg_time, char *name, char *test_id)
{
    // --- WRITE RESULTS TO FILE --- //
    char *algoresult = generateFilename(name, test_id, "json");
    FILE *algoresult_fp = openFile(algoresult, "w");
    writePartitions(algoresult_fp, result, p->rows);
    fclose(algoresult_fp);
    // --- WRITE TIME TO FILE --- //
    char *algotime = generateFilename(name, test_id, "txt");
    FILE *algotime_fp = openFile(algotime, "w");
    writeTime(algotime_fp, avg_time);
    fclose(algotime_fp);
}

bool *run_algo(Partitions *p, void (*func)(Partitions *, bool *), char *name, char *test_id, char *repetitions)
{
    // --- SETUP --- //
    bool *result = (bool *)malloc(p->rows * sizeof(bool));

    // --- EXECTUTION --- //
    double avg_time = 0;
    for (int i = 0; i < atoi(repetitions); i++)
    {
        double start = omp_get_wtime();
        func(p, result);
        double end = omp_get_wtime();
        avg_time += end - start;
    }
    avg_time = avg_time / atoi(repetitions);

    output_algo(p, result, avg_time, name, test_id); // Write results to file

    free(result);
}

void algo(Partitions *p, char *test_id, char *repetitions)
{
    run_algo(p, seq, "seq", test_id, repetitions);
    run_algo(p, sgl_stc, "sgl_stc", test_id, repetitions);
    run_algo(p, sgl_dyn, "sgl_dyn", test_id, repetitions);

    return;
}
