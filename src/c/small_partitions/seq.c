#include <stdbool.h>

#include "../lib/parallelNP.h"
#include "./small_partitions.h"

bool seq(int *arr, int size)
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