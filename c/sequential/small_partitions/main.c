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
#include <string.h>
#include <stdint.h>

#include "../../lib/parallelNP.h"

#define NAME "C > sequential > small_partitions"
int verbose = 0;

bool partition(int *arr, int size)
{
    unsigned long long int index = 1 << (size - 1);

    for (unsigned long long int i = 0; i < index; i++)
    {
        int array1[size];
        int index1 = 0;
        int array2[size];
        int index2 = 0;

        for (int j = 0; j < size; j++)
        {
            if (i & (1 << j))
            {
                array1[index1] = arr[j];
                index1++;
            }
            else
            {
                array2[index2] = arr[j];
                index2++;
            }
        }

        if (set_sum(array1, index1) == set_sum(array2, index2))
        {
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    // At least two arguments expected:
    // 1. Program name
    // 2. Test input file name
    // 3. Output file name (results / timings)
    // 4. (Optional) Verbose flag

    for (uint8_t i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--verbose") == 0)
        {
            verbose = 1;
        }
    }

    // 1. Read the input file
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "%s )-: Unable to open file %s\n", NAME, argv[1]);
        return 1;
    }

    char *buffer = readFile(inputFile);

    // 2. Parse the buffer into json
    // 3. Convert json into an array (of arrays) of integers
    dimensions *d = dims(buffer);
    int **arr = json2partitions(buffer, d);

    // 4.a Perform the partitioning
    if (!verbose)
    {
        for (int i = 0; i < d->rows; i++)
            partition(arr[i], d->cols[i]);
    }

    // 4.b Write the results to the output file
    if (verbose)
    {
        json_object *jarray = json_object_new_array();
        
        FILE *outFile = fopen(argv[2], "w");
        if (outFile == NULL)
        {
            fprintf(stderr, "[%s:] Error opening file %s\n", NAME, argv[2]);
            return 1;
        }
        writeString(outFile, "");

        for (int i = 0; i < d->rows; i++)
        {
            int result = partition(arr[i], d->cols[i]);
            json_object *jbool = json_object_new_boolean(result);
            json_object_array_add(jarray, jbool);
        }

        writeJsonObject(outFile, jarray);
        json_object_put(jarray);
        fclose(outFile);
    }

    fclose(inputFile);
    free(arr);
    free(buffer);

    return 0;
}