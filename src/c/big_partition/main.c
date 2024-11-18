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

#include "../lib/parallelNP.h"
#include "./big_partition.h"

#define NAME "C > big_partition"

void print(char *file, bool result) {
    json_object *jarray = json_object_new_array();

    json_object *jbool = json_object_new_boolean(result);
    json_object_array_add(jarray, jbool);

    FILE *outFile = fopen(file, "w");
    if (outFile == NULL)
    {
        fprintf(stderr, "[%s:] Error opening file %s\n", NAME, file);
        return;
    }
    writeString(outFile, "");

    writeJsonObject(outFile, jarray);
    json_object_put(jarray);

    fclose(outFile);
}

int main(int argc, char *argv[])
{
    bool verbose = false;
    char *test;
    char *outS;
    char *outP;
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
    {
        fprintf(stderr, ">->->\n");
        fprintf(stderr, "[WARNING - Unrecognized Arguments] Try:\n");
        fprintf(stderr, "%s [-v] -t <test> -x <sequential> -y <parallel>\n", argv[0]);
        fprintf(stderr, "<-<-<\n");
        return 1;
    }

    // 1) Read the input file
    FILE *inputFile = fopen(test, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "%s )-: Unable to open file %s\n", NAME, argv[1]);
        return 1;
    }

    char *buffer = readFile(inputFile);

    // 2) Parse the buffer into json and
    // 3) Convert json into an array (of arrays) of integers
    dimensions *d = dims(buffer);
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

    // 4) Write the results to the output
    if (verbose)
    {
        print(outS, resultS);
        print(outP, resultP);
    }


    free(arr);
    fclose(inputFile);
    free(buffer);

    return 0;
}