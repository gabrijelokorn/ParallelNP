#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <json-c/json.h>

#include "../lib/parallelNP.h"
#include "./kamada_kawai.h"

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
    {
        fprintf(stderr, ">->->\n");
        fprintf(stderr, "[WARNING - Unrecognized Arguments] Try:\n");
        fprintf(stderr, "%s [-v] -t <test> -x <sequential> -y <parallel>\n", argv[0]);
        fprintf(stderr, "<-<-<\n");
        return 1;
    }

    int n;
    float k;
    int **vertices;
    int **edges;

    // 1) Read the input file
    char *buffer = readFile(test);

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

    return 0;
}