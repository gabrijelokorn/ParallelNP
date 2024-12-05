#include <omp.h>

#include "large.h"

int set_sum_par(int *arr, int size, unsigned long long int index)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
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

    int total_sum = set_sum_par(arr, size, (1 << (size)) - 1);
    int half_sum = total_sum / 2;
    if (total_sum % 2 != 0)
        return false;

    bool found = false;

#pragma omp teams distribute parallel for shared(found)
    for (int i = 0; i < possibilities; i++)
    {
        if (found)
            continue;

        int sum = set_sum_par(arr, size, i);
        if (sum == half_sum)
            found = true;
    }

    return found;
}