#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <json-c/json.h>
#include <omp.h>
#include <time.h>
#include <string.h>

#include "../common/parallelNP.h"

#include "./kamada_kawai.h"
#include "./algo/algo.h"

#include "./kamada_kawai2csv.h"
#include "./json2kamada_kawai.h"

int main(int argc, char *argv[])
{
    char *test_path = NULL;    // Initialize to NULL
    char *test_id = NULL;      // Initialize to NULL  
    char *repetitions = NULL;  // Initialize to NULL
    bool help = false;
    
    int opt;
    while ((opt = getopt(argc, argv, ":t:x:r:")) != -1)
    {
        switch (opt)
        {
            case 't':
            test_path = optarg;
            break;
            case 'x':
            test_id = optarg;
            break;
            case 'r':
            repetitions = optarg;
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
    
    // Read the input file
    FILE *test_file = openFile(test_path, "r");
    char *buffer = readFile(test_file);
    fclose(test_file);
    
    // json -> KamadaKawai struct
    KamadaKawai *kamadaKawai = json2KamadaKawai(buffer);
    
    // Run the algorithm
    algo(kamadaKawai, test_id, repetitions);

    // Free the allocated memory
    free(buffer);
    free(kamadaKawai);
    
    return 0;
}