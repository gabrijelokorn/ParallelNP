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

#include "../../lib/read.h"
#include "../../lib/write.h"
#include "../../lib/array.h"
#include "../../lib/set.h"

#define NAME "Sequential C - Big Partition"

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
    // At least two arguments expected - input file name and output file name
    if (argc < 3)
    {
        printf("[%s:] Internal error - try: %s <input file> <output file>\n", NAME, argv[0]);
        return 1;
    }

    int size = 0;
    int *arr = NULL;
    read1d(argv, &arr, &size);

    if (partition(arr, size))
        writeString(argv[2], "w", "YES\n");
    else
        writeString(argv[2], "w", "NO\n");

    free(arr);
    return 0;
}