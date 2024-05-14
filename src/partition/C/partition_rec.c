/**
 * @file partition_rec.c
 * @author your name (you@domain.com)
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

#include "read.h"
#include "array.h"
#include "set.h"

#define DEBUG 1

bool partition_rec(int *arr, int size, long long unsigned int index, int combinations)
{
    if (index >= combinations) return false;

    int array1[size];
    int index1 = 0;
    int array2[size];
    int index2 = 0;

    for (int j = 0; j < size; j++)
    {
        if (index & (1 << j))
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
        printf("Array 1: ");
        printArray(array1, index1);
        printf("Array 2: ");
        printArray(array2, index2);
        return true;
    }

    partition_rec(arr, size, index + 1, combinations);
    return false;
}

int main(int argc, char *argv[])
{
    // At least one argument expected
    if (argc < 2)
    {
        printf("Usage: %s <number1> <number2> ... <numberN>\n", argv[0]);
        return 1;
    }

    int size = 0;
    int *arr = NULL;
    readFile(argv, &arr, &size);

    if (DEBUG)
        printArray(arr, size);

    if (partition_rec(arr, size, 0, (1 << (size - 1))))
        printf("Solution not found\n");

    free(arr);
    return 0;
}