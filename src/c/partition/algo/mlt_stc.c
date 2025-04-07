#include <stdbool.h>

#include "algo.h"

void mlt_stc(Partitions *p, bool *result)
{
    {
#pragma omp parallel default(none) shared(p, result)
#pragma omp for schedule(static, 5)
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

            for (int j = 0; j < numOfCombinations; j++)
            {
                int sum = partition_sum(row, size, j);
                if (sum == half_problem_sum)
                {
                    result[i] = true;
                    break;
                }
            }
        }
    }
}