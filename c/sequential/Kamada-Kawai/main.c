#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/parallelNP.h"

#define NAME "C > sequential > Kamada-Kawai"

int main(int argc, char *argv[])
{
    // At least two arguments expected - input file name and output file name
    if (argc < 3)
    {
        printf("[%s:] Internal error - try: %s <input file> <output file>\n", NAME, argv[0]);
        return 1;
    }

    int n;
    
    int K;
    int vertices;

    #ifdef VERBOSE
        writeString(argv[2], "w", "");
        writeString(argv[2], "a", "YES\n");
    #endif

    #ifndef VERBOSE
    #endif

    return 0;
}