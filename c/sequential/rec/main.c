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
#include <string.h>
#include <stdint.h>

#include "../lib/read.h"
#include "../lib/array.h"
#include "../lib/set.h"

bool DEBUG = 0;

bool partition_rec(int *arr, int size, int index, int sum1, int sum2)
{
    if (index > size)
        return false;

    if (sum1 == sum2)
        return true;

    bool include = partition_rec(arr, size, index + 1, sum1 + arr[index], sum2 - arr[index]);
    bool exclude = partition_rec(arr, size, index + 1, sum1, sum2);

    return include || exclude;
}

int main(int argc, char *argv[])
{
    // At least one argument expected
    if (argc < 2)
    {
        printf("Usage: %s <number1> <number2> ... <numberN>\n", argv[0]);
        return 1;
    }

    for (uint8_t i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
            DEBUG = 1;
    }

    int size = 0;
    int *arr = NULL;
    readFile(argv, &arr, &size);

    if (DEBUG)
        printArray(arr, size);

    if (!partition_rec(arr, size, 0, 0, set_sum(arr, size)))
        printf("[%s]: solution not found\n", argv[0]);
    else
        printf("[%s]: solution found\n", argv[0]);

    free(arr);
    return 0;
}