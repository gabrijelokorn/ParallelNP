#include <stdbool.h>
#include <omp.h>

#include "algo.h"

void nested(Partitions *p, bool *result)
{
    omp_set_nested(1);
#pragma omp parallel default(none) shared(p, result)
#pragma omp for schedule(dynamic, 5)
    for (int i = 0; i < p->rows; i++)
    {
        result[i] = false;

        int *row = p->arr[i];
        int size = p->cols[i];

        unsigned long long int numOfCombinations = 1 << (size - 1);
        unsigned long long int allNumbersMask = ((unsigned long long int)1 << size) - 1;

        int problem_sum = partition_sum(row, size, allNumbersMask);
        if (problem_sum % 2 != 0)
            continue;
        int half_problem_sum = problem_sum / 2;

        {
            bool found = false;
            #pragma omp parallel default(none) shared(row, size, numOfCombinations, half_problem_sum, result, i, found)
            #pragma omp for schedule(static, 5)
            for (int j = 0; j < numOfCombinations; j++)
            {
                if (found)
                    continue;
                int sum = partition_sum(row, size, j);
                if (sum == half_problem_sum)
                {
                    result[i] = true;
                    found = true;
                }
            }
        }
    }
}