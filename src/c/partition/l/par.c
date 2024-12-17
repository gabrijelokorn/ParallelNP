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
    unsigned long long int possibilities = 1 << (size - 1);
    unsigned long long int complete_set = ((unsigned long long int)1 << size) - 1;

    int problem_sum = large_sum_par(arr, size, complete_set);
    if (problem_sum % 2 != 0)
        return false;
    int half_problem_sum = problem_sum / 2;

    bool found = false;

#pragma omp parallel default(none) shared(found, possibilities, arr, size, half_problem_sum)
    {
#pragma omp for
        for (unsigned long long int i = 0; i < possibilities; i++)
        {
            if (found)
                continue;
            int sum = large_sum_par(arr, size, i);
            if (sum == half_problem_sum)
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