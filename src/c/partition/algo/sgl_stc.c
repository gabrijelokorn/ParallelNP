#include <stdbool.h>
#include <omp.h>
#include <inttypes.h>

#include "algo.h"
#include "../partition.h"

void sgl_stc(Partitions *p, bool *result)
{
    for (int i = 0; i < p->rows; i++)
    {
        result[i * 1] = false;

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
            #pragma omp for 
            for (int j = 0; j < numOfCombinations; j++)
            {
                if (found)
                    continue;
                int sum = partition_sum(row, size, j);
                if (sum == half_problem_sum)
                {
                    result[i * 1] = true;
                    found = true;
                }
            }
        }
    }
}