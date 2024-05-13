/**
 * @file partition_iter.c
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

#include "read.h"
#include "array.h"
#include "set.h"

#define DEBUG 1

bool partition_iter (int *arr, int size) {
    unsigned long long int index = 1 << (size - 1);

    for (unsigned long long int i = 0; i < index; i++) {
        int array1[size];
        int index1 = 0;
        int array2[size];
        int index2 = 0;

        for (int j = 0; j < size; j++) {
            if (i & (1 << j)) {
                array1[index1] = arr[j];
                index1++;
            } else {
                array2[index2] = arr[j];
                index2++;
            }
        }


        if (set_sum(array1, index1) == set_sum(array2, index2)) {
            if (DEBUG) {
                printf("Array 1: ");
                printArray(array1, index1);
                printf("Array 2: ");
                printArray(array2, index2);
            }
            return true;
        }

    }

    return false;
}

int main(int argc, char *argv[])
{
    // At least one argument expected
    if (argc < 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    int size = 0;
    int *arr = NULL;
    readFile(argv, &arr, &size);

    if (DEBUG) printArray(arr, size);

    if (!partition_iter(arr, size))
        printf("Solution not found\n");
    else
        printf("Solution found\n");


    free(arr);
    return 0;
}