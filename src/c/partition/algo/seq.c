#include <stdbool.h>

#include "algo.h"

bool seq(Partitions *p)
{
    bool result = false;

    for (int i = 0; i < p->rows; i++)
    {
        int *row = p->arr[i];
        int size = p->cols[i];

        unsigned long long int numOfCombinations = 1 << (size - 1);
        unsigned long long int allNumbersMask = ((unsigned long long int)1 << size) - 1;

        int problem_sum = partition_sum(row, size, allNumbersMask);
        if (problem_sum % 2 != 0)
            continue;
        int half_problem_sum = problem_sum / 2;

        for (unsigned long long int j = 0; j < numOfCombinations; j++)
        {
            int sum = partition_sum(row, size, j);
            if (sum == half_problem_sum)
            {
                result = true;
                break;
            }
        }
    }

    return result;
}