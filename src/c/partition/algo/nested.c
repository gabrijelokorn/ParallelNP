#include <stdbool.h>
#include <omp.h>

#include "algo.h"

bool *nested(Partitions *p, int **arr)
{
    omp_set_nested(1);

    bool *result = (bool *)malloc(p->rows * sizeof(bool));

#pragma omp parallel default(none) shared(arr, p, result)
#pragma omp for schedule(dynamic, 5)
    for (int i = 0; i < p->rows; i++)
    {
        result[i] = false;

        int *row = arr[i];
        int size = p->cols[i];

        unsigned long long int numOfCombinations = 1 << (size - 1);
        unsigned long long int allNumbersMask = ((unsigned long long int)1 << size) - 1;

        int problem_sum = partition_sum(row, size, allNumbersMask);
        if (problem_sum % 2 != 0)
            continue;
        int half_sum = problem_sum / 2;

        {
            bool found = false;
            #pragma omp parallel default(none) shared(row, size, numOfCombinations, half_sum, result, i, found)
            #pragma omp for schedule(static, 5)
            for (int j = 0; j < numOfCombinations; j++)
            {
                if (found)
                    continue;
                int sum = partition_sum(row, size, j);
                if (sum == half_sum)
                {
                    result[i] = true;
                    found = true;
                }
            }
        }
    }

    return result;
}