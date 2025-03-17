#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <json-c/json.h>
#include <omp.h>
#include <time.h>
#include <string.h>

#include "../common/parallelNP.h"

#include "./kamada_kawai.h"
#include "./algo/algo.h"

#include "./kamada_kawai2csv.h"
#include "./json2kamada_kawai.h"

int main(int argc, char *argv[])
{
    bool verbose = false;
    char *test;
    char *nThreadsStr;
    char *num;
    bool help = false;

    int opt;
    while ((opt = getopt(argc, argv, ":t:x:n:v")) != -1)
    {
        switch (opt)
        {
        case 't':
            test = optarg;
            break;
        case 'x':
            num = optarg;
            break;
        case 'n':
            nThreadsStr = optarg;
            break;
        case 'v':
            verbose = true;
            break;
        case ':':
        case '?':
            help = true;
            break;
        }
    }
    if (optind < argc)
        help = true;

    if (help)
        error_args(argv[0]);

    // Set the number of threads
    int nThreads = atoi(nThreadsStr);
    if (nThreads < 1)
        error_args(argv[0]);

    int n;
    float k;

    // Read the input file
    FILE *testF = openFile(test, "r");
    char *buffer = readFile(testF);
    fclose(testF);

    // json -> KamadaKawai struct
    KamadaKawai *kamadaKawai = json2KamadaKawai(buffer);
    free(buffer);

    // Run the algorithm
    algo(kamadaKawai, nThreads, verbose, num);
    free(kamadaKawai);

    return 0;
}