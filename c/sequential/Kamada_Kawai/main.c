#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/parallelNP.h"

#define NAME "C > sequential > Kamada-Kawai"
uint8_t verbose = 0;

int main(int argc, char *argv[])
{
    // At least 5 arguments expected:
    // 1. Program name
    // 2. Test input file
    // 3. Output file - number of vertices
    // 4. Output file - coordinates of the vertices
    // 5. Output file - edges between the vertices
    // 6. (Optional) Verbose flag
    if (argc < 5)
    {
        fprintf(stderr, "%s )-: Unexpected arguments. Try %s <input file> <points.csv> <coords.csv> <edges.csv>\n", NAME, argv[0]);
        return 1;
    }

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

        // Print results into 3 different files
        // 1. points.csv - coordinates of the vertices
        // 2. edges.csv - edges between the vertices
        // 3. distances.csv - distances between the vertices
    }
    return 0;
}