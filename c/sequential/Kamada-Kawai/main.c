#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/parallelNP.h"

#define NAME "C > sequential > Kamada-Kawai"

int main(int argc, char *argv[])
{
    // At least two arguments expected - input file name and output file name
    if (argc < 5)
    {
        printf("[%s:] Internal error - try: %s <points.txt> <coordinates.txt> <edges.txt> <output video.avi>\n", NAME, argv[0]);
        return 1;
    }

    int n;
    
    int K;
    int vertices;

    return 0;
}