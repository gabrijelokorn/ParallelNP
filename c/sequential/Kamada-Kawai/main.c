#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/parallelNP.h"

#define NAME "C > sequential > Kamada-Kawai"

int main(int argc, char *argv[])
{
    // At least two arguments expected - input file name and output file name
    if (argc < 4)
    {
        printf("[%s:] Internal error - try: %s <input file> <coordinates.txt> <edges.txt> <output video.avi>\n", NAME, argv[0]);
        return 1;
    }

    int n;
    
    int K;
    int vertices;

#ifdef VERBOSE
#endif

#ifndef VERBOSE
#endif

    return 0;
}