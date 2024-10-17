#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/parallelNP.h"

#define NAME "C > sequential > Kamada-Kawai"

int main(int argc, char *argv[])
{
    // At least two arguments expected - input file name and output file name
    if (argc < 6)
    {
        printf("[%s:] Internal error - try: %s <coordinates_input.txt> <edges_input.txt> <points.txt> <coordinates.txt> <edges.txt> \n", NAME, argv[0]);
        return 1;
    }

    int n;
    
    int K;
    int vertices;

#ifdef VERBOSE  
    // Print results into 3 different files
    // 1. points.txt - coordinates of the vertices
    // 2. edges.txt - edges between the vertices
    // 3. distances.txt - distances between the vertices
#endif

#ifndef VERBOSE

#endif

    return 0;
}