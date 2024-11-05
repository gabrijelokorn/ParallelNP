#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/parallelNP.h"

#define NAME "C > sequential > Kamada-Kawai"
uint8_t verbose = 0;

void KamadaKawaiToString (KamadaKawai *kk) {
    printf("Kamada-Kawai:\n");
    printf("n: %d\n", kk->n);
    printf("m: %d\n", kk->m);
    printf("k: %f\n", kk->k);

    printf("edges:\n");
    for (int i = 0; i < kk->m; i++) {
        printf("%d: [%d,%d]\n", i, kk->edges[i][0], kk->edges[i][1]);
    }

    printf("coords:\n");
    for (int i = 0; i < kk->n; i++) {
        printf("%d: [%d,%d]\n", i, kk->coordinates[i][0], kk->coordinates[i][1]);
    }

}

int main(int argc, char *argv[])
{
    // At least 3 arguments expected:
    // 1. Program name
    // 2. Test input file
    // (3-5). Output file(s) - (number of vertices, coordinates of the vertices, edges between the vertices) / timings
    // 6. (Optional) Verbose flag

    for (uint8_t i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--verbose") == 0)
        {
            verbose = 1;
        }
    }

    int n;
    double k;
    int **vertices;
    int **edges;

    // 1. Read the input file
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "%s )-: Unable to open file %s\n", NAME, argv[1]);
        return 1;
    }

    char *buffer = readFile(inputFile);

    // 2. Parse the input file into json object
    KamadaKawai *kamadaKawai = json2KamadaKawai(buffer);

    if (!verbose)
    {
    }

    if (verbose)
    {
        KamadaKawaiToString(kamadaKawai);
        // Print results into 3 different files
        // 1. points.csv - coordinates of the vertices
        // 2. edges.csv - edges between the vertices
        // 3. distances.csv - distances between the vertices
    }
    return 0;
}