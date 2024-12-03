#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <json-c/json.h>

#include "../common/parallelNP.h"
#include "./kamada_kawai.h"
#include "./json2kamada_kawai.h"
#include "./kamada_kawai2csv.h"

#define NAME "C > Kamada-Kawai"

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
    Vertices *resultS = seq(kamadaKawai);

    // Parallel
    // Vertices *resultP = par(kamadaKawai);

    // Write the output files
    if (verbose)
    {
        FILE *fileS = fopen(outS, "w");
        writeVertices(fileS, resultS, kamadaKawai->n);

        // FILE *fileP = fopen(outP, "w");

        fclose(fileS);
        // fclose(fileP);
    }

    free(buffer);
    free(kamadaKawai);

    free(resultS);
    fclose(testF);

    return 0;
}