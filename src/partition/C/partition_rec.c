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

bool partition_rec_helper (int *arr, int size, int index, int sum, int target) {
    if (sum == target) return true;
    if (sum > target || index >= size) return false;

    return partition_rec_helper(arr, size, index + 1, sum + arr[index], target) ||
           partition_rec_helper(arr, size, index + 1, sum, target);
}

bool partition_rec (int *arr, int size) {
    int sum = set_sum(arr, size);
    if (sum % 2 != 0) return false;

    return partition_rec_helper(arr, size, 0, 0, sum / 2);
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

    if (DEBUG) printArray(arr, size);

    if (!partition_rec(arr, size))
        printf("No partition found\n");
    else
        printf("Partition found\n");

    free(arr);
    return 0;
}