#include <omp.h>

#include "large.h"

int large_sum_par(int *arr, int size, unsigned long long int index)
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
    unsigned long long int combs = 1 << (size - 1);
    unsigned long long int all = ((unsigned long long int)1 << size) - 1;

    int problem_sum = large_sum_par(arr, size, all);
    if (problem_sum % 2 != 0)
        return false;
    int half_sum = problem_sum / 2;

    bool found = false;

#pragma omp parallel default(none) shared(found, combs, arr, size, half_sum)
    {
#pragma omp for
        for (unsigned long long int i = 0; i < combs; i++)
        {
            if (found)
                continue;
            int sum = large_sum_par(arr, size, i);
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