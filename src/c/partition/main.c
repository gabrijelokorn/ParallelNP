/**
 * @file main.c
 * @author Gabrijel Okorn (gabrijel.okorn@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-04-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <json-c/json.h>

#include "../common/parallelNP.h"

#include "./partition.h"
#include "./algo/algo.h"

#include "./json2partitions.h"

int main(int argc, char *argv[])
{
    bool verbose = false;
    char *test;
    char *num;
    bool help = false;

    int opt;
    while ((opt = getopt(argc, argv, ":vt:x:")) != -1)
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
            num = optarg;
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
    FILE *testF = openFile(test, "r");
    char *buffer = readFile(testF);
    fclose(testF);
    
    // json -> partitions
    Partitions *p = get_partitions(buffer);
    // partitions -> array
    int **arr = json2partitions(buffer, p);
    free(buffer);
    
    // Run the algorithm
    algo(p, arr, num, verbose);
    free(arr);

    return 0;
}