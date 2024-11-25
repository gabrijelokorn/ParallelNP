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
#include "./big_partition.h"

#define NAME "C > big_partition"

int main(int argc, char *argv[])
{
    bool verbose = false;
    char *test;
    FILE *outS;
    FILE *outP;
    bool help = false;

    int opt;
    while ((opt = getopt(argc, argv, ":t:vx:y:")) != -1)
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
            outS = openFile(optarg, "w");
            break;
        case 'y':
            outP = openFile(optarg, "w");
            break;
        case ':':
            help = true;
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

    // json -> partitions
    Partitions *d = get_partitions(buffer);
    // partitions -> array
    int **arr = json2partitions(buffer, d);

    // Sequential
    bool resultS = false;
    for (int i = 0; i < d->rows; i++)
    {
        resultS = seq(arr[i], d->cols[i]);
    }

    // Parallel
    bool resultP = false;
    // for (int i = 0; i < d->rows; i++)
    // {
    // }

    // Write the results to the output
    if (verbose)
    {
        writePartitions(outS, &resultS, 1);
        // writePartitions(outP, &resultP, 1);
    }

    free(arr);
    free(buffer);
    fclose(testF);
    fclose(outS);
    fclose(outP);

    return 0;
}