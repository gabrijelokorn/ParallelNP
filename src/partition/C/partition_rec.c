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

bool partition_rec(int *arr, int size, int index, int sum1, int sum2)
{
    if (index > size) return false;

    if (sum1 == sum2)
    {
        printf("Solution found\n");
        return true;
    }

    return partition_rec(arr, size, index + 1, sum1 + arr[index], sum2 - arr[index]) ||
           partition_rec(arr, size, index + 1, sum1, sum2);
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

    if (!partition_rec(arr, size, 0, 0, set_sum(arr, size)))
        printf("Solution not found\n");

    free(arr);
    return 0;
}