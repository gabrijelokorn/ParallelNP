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
    char *test_path;
    char *test_id;
    char *r;
    int repetitions;
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
            r = optarg;
            repetitions = atoi(r);
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
    FILE *testF = openFile(test_path, "r");
    char *buffer = readFile(testF);
    fclose(testF);

    // json -> partitions
    Partitions *p = get_partitions(buffer);

    // Run the algorithm
    algo(p, test_id, repetitions);

    // Free the allocated memory
    free(buffer);
    free(p);

    return 0;
}