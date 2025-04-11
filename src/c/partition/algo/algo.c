#include <stdbool.h>
#include <omp.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "../../common/parallelNP.h"
#include "algo.h"

void output_algo (Partitions *p, bool *result, double elapsed, char *name, char *test_id)
{
    // --- WRITE RESULTS TO FILE --- //
    char *algoresult = generateFilename(name, test_id, "json");
    FILE *algoresult_fp = openFile(algoresult, "w");
    writePartitions(algoresult_fp, result, p->rows);
    fclose(algoresult_fp);
    // --- WRITE TIME TO FILE --- //
    char *algotime = generateFilename(name, test_id, "txt");
    FILE *algotime_fp = openFile(algotime, "w");
    writeTime(algotime_fp, elapsed);
    fclose(algotime_fp);
}

bool *run_algo(Partitions *p, void (*func)(Partitions *, bool *), char *name, char *test_id)
{
    // --- SETUP --- //
    bool *result = (bool *)malloc(p->rows * sizeof(bool));

    // --- EXECTUTION --- //
    double start = omp_get_wtime();
    func(p, result);
    double end = omp_get_wtime();

    output_algo(p, result, end - start, name, test_id); // Write results to file

    free(result);
}

void algo(Partitions *p, char *test_id)
{
    run_algo(p, seq, "seq", test_id);
    run_algo(p, sgl_stc, "sgl_stc", test_id);
    run_algo(p, sgl_dyn, "sgl_dyn", test_id);
    run_algo(p, mlt_stc, "mlt_stc", test_id);
    run_algo(p, mlt_dyn, "mlt_dyn", test_id);
    run_algo(p, nested, "nested", test_id);

    return;
}
