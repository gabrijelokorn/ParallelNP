#include <omp.h>

#include "large.h"

int par_sum(int *arr, int size, unsigned long long int index)
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

bool par(int *arr, int size)
{
    unsigned long long int possibilities = 1 << (size - 1);
    unsigned long long int complete_set = ((unsigned long long int)1 << size) - 1;

    int total_sum = par_sum(arr, size, complete_set);
    if (total_sum % 2 != 0)
        return false;
    int half_sum = total_sum / 2;

    bool found = false;

#pragma omp parallel shared(found)
    {
#pragma omp for
        for (unsigned long long int i = 0; i < possibilities; i++)
        {
            int sum = par_sum(arr, size, i);
            if (sum == half_sum)
            {
                found = true;
#pragma omp cancel for
            }
#pragma omp cancellation point for
        }
    }

    return found;
}