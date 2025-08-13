#include <omp.h>
#include <inttypes.h>
#include <stdio.h>

#include "algo.h"
#include "../partition.h"

bool sgl_stc(Partitions *p)
{
    bool found = false;

    for (int i = 0; i < p->rows; i++)
    {
        int *arr = p->arr[i];
        int size = p->cols[i];
        unsigned long long int numOfCombinations = 1 << (size - 1);
        unsigned long long int allNumbersMask = ((unsigned long long int)1 << size) - 1;

        int problem_sum = partition_sum(arr, size, allNumbersMask);
        if (problem_sum % 2 != 0)
            continue;
        int half_problem_sum = problem_sum / 2;

        {
#pragma omp parallel default(none) shared(arr, size, numOfCombinations, half_problem_sum, found)
#pragma omp for schedule(static)
            for (unsigned long long int j = 0; j < numOfCombinations; j++)
            {
#pragma omp cancelation point

                int sum = partition_sum(arr, size, j);
                if (sum == half_problem_sum)
                {
#pragma omp atomic write
                    found = true;
#pragma omp cancel for
                }
            }
        }
    }
    return found;
}