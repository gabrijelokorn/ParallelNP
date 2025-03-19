#include "partition.h"

int partition_sum(int *arr, int size, unsigned long long int index)
{
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        if (index & (1 << i))
        {
            sum += arr[size - 1 - i];
        }
    }
    return sum;
}