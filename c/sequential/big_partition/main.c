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

#define NAME "C > sequential > big_partition"

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
    // 3. Output file name
    if (argc < 3)
    {
        fprintf(stderr, "%s )-: Internal error - try: %s <input file> <output file>\n", NAME, argv[0]);
        return 1;
    }

    // 1. Open the test file
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "%s )-: Error opening file %s\n", NAME, argv[1]);
        return 1;
    }

    // 2. Determine file size
    fseek(inputFile, 0, SEEK_END);      // Seek to the end of the file
    int size = getFileSize(inputFile);  // Get the current file pointer
    rewind(inputFile);                  // Rewind the file pointer to the beginning

    // 3. Allocate memory for the file
    char *buffer = (char *)malloc((size + 1) * sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr, "%s )-: Error allocating memory\n", NAME);
        fclose(inputFile);
        return 1;
    }

    // 4. Read the file into a buffer
    fread(buffer, size, 1, inputFile);
    // Null terminate the buffer
    buffer[size] = '\0';

    // 5. Parse the buffer into json and
    // 6. Convert json into an array (of arrays) of integers
    dimensions *d = dims(buffer);
    int **arr = json2partitions(buffer, d);

    json_object *jarray = json_object_new_array();

    // 7.a Perform the partitioning
#ifndef VERBOSE
    for (int i = 0; i < d->rows; i++)
        partition(arr[i], d->cols[i]);
#endif

    // 7.b Write the results to the output file
#ifdef VERBOSE
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
#endif

    free(arr);
    fclose(inputFile);
    free(buffer);

    return 0;
}