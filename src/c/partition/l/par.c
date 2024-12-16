#include <omp.h>

#include "large.h"

int large_par_sum(int *arr, int size, unsigned long long int index)
{
    int sum = 0;
#pragma omp reduction(+ : sum)
    for (int i = 0; i < size; i++)
    {
        if (index & (1 << i))
        {
            sum += arr[size - 1 - i];
        }
    }
    return sum;
}

bool large_par(int *arr, int size) // Solution 1
{
    unsigned long long int possibilities = 1 << (size - 1);
    unsigned long long int complete_set = ((unsigned long long int)1 << size) - 1;

    int total_sum = large_par_sum(arr, size, complete_set);
    if (total_sum % 2 != 0)
        return false;
    int half_sum = total_sum / 2;

    bool found = false;

#pragma omp parallel default(none) shared(found, possibilities, arr, size, half_sum)
    {
#pragma omp for
        for (unsigned long long int i = 0; i < possibilities; i++)
        {
            if (found)
                continue;
            int sum = large_par_sum(arr, size, i);
            if (sum == half_sum)
            {
#pragma omp critical
                {
                    found = true;
#pragma omp flush(found)
                }
            }
        }
    }

    return found;
}