#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <json-c/json.h>
#include <omp.h>
#include <time.h>

#include "../common/parallelNP.h"

#include "./kamada_kawai.h"

#include "./kamada_kawai2csv.h"
#include "./json2kamada_kawai.h"

int main(int argc, char *argv[])
{
    bool verbose = false;
    char *test;
    char *outS;
    char *outP;
    bool help = false;

    int opt;
    while ((opt = getopt(argc, argv, ":t:x:y:v")) != -1)
    {
        switch (opt)
        {
        case 't':
            test = optarg;
            break;
        case 'v':
            verbose = true;
            break;
        case 'x':
            outS = optarg;
            break;
        case 'y':
            outP = optarg;
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

    int n;
    float k;

    // Read the input file
    FILE *testF = openFile(test, "r");
    char *buffer = readFile(testF);

    // json -> KamadaKawai struct
    KamadaKawai *kamadaKawai = json2KamadaKawai(buffer);

    // Sequential
    double start_seq = omp_get_wtime();
    Vertices *resultS = seq(kamadaKawai);
    double end_seq = omp_get_wtime();

    // Reassign the coordinates
    for (int i = 0; i < kamadaKawai->n; i++)
    {
        kamadaKawai->coords[i].x = resultS->coords[i].x;
        kamadaKawai->coords[i].y = resultS->coords[i].y;
    }

    // Parallel
    double start_par = omp_get_wtime();
    Vertices *resultP = par(kamadaKawai);
    double end_par = omp_get_wtime();

    // Write the output files
    if (verbose)
    {
        FILE *fileS = fopen(outS, "w");
        writeVertices(fileS, resultS, kamadaKawai->n);

        FILE *fileP = fopen(outP, "w");
        writeVertices(fileP, resultP, kamadaKawai->n);

        fclose(fileS);
        fclose(fileP);

        // Print the times
        printf("Sequential: %f seconds\n", end_seq - start_seq);
        printf("Parallel: %f seconds\n", end_par - start_par);
    }

    free(buffer);
    free(kamadaKawai);

    free(resultS);
    fclose(testF);

    return 0;
}