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
    FILE *outS;
    FILE *outP;
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
            outS = openFile(optarg, "w");
            break;
        case 'y':
            outP = openFile(optarg, "w");
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
    int **vertices;
    int **edges;

    // 1) Read the input file
    FILE *testF = openFile(test, "r");
    char *buffer = readFile(testF);

    // 2) json -> KamadaKawai struct
    KamadaKawai *kamadaKawai = json2KamadaKawai(buffer);

    // 3) Solve
    // Sequential
    Vertices *resultS = seq(kamadaKawai);

    // Parallel

    // 3) Write the output files
    if (verbose)
    {
        writeVertices(outS, resultS, kamadaKawai->n);
    }

    free(kamadaKawai);
    free(vertices);
    free(edges);
    free(resultS);
    free(buffer);
    
    fclose(testF);
    fclose(outS);
    fclose(outP);

    return 0;
}