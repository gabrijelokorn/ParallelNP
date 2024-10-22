#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/parallelNP.h"

#define NAME "C > sequential > Kamada-Kawai"

int main(int argc, char *argv[])
{
    // At least 5 arguments expected:
    // 1. Program name
    // 2. Test input file
    // 3. Output file - number of vertices
    // 4. Output file - coordinates of the vertices
    // 5. Output file - edges between the vertices
    if (argc < 5)
    {
        fprintf(stderr, "%s )-: Unexpected arguments. Try %s <input file> <points.csv> <coords.csv> <edges.csv>\n", NAME, argv[0]);
        return 1;
    }

    int n;
    int K;
    int vertices;

#ifndef VERBOSE

#endif

#ifdef VERBOSE  
    // Print results into 3 different files
    // 1. points.csv - coordinates of the vertices
    // 2. edges.csv - edges between the vertices
    // 3. distances.csv - distances between the vertices
#endif


    return 0;
}