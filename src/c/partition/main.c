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

#define NAME "C > big_partition"

int main(int argc, char *argv[])
{
    bool verbose = false;
    bool l = false;
    char *test;
    char *outS;
    char *outP;
    bool help = false;

    int opt;
    while ((opt = getopt(argc, argv, ":vlt:x:y:")) != -1)
    {
        switch (opt)
        {
        case 't':
            test = optarg;
            break;
        case 'v':
            verbose = true;
            break;
        case 'l':
            l = true;
            break;
        case 'x':
            outS = optarg;
            break;
        case 'y':
            outP = optarg;
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
    Partitions *p = get_partitions(buffer);
    // partitions -> array
    int **arr = json2partitions(buffer, p);

    if (l)
        large(arr, p, verbose, outS, outP);
    else
        small(arr, p, verbose, outS, outP);

    free(buffer);
    free(arr);
    fclose(testF);

    return 0;
}