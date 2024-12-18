#include <stdbool.h>

#include "small.h"

int small_sum_par(int *arr, int size, unsigned long long int index)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (index & (1 << i))
        {
            sum += arr[size - 1 - i];
        }
    }
    return sum;
}

bool *small_par(int **arr, Partitions *p)
{
    bool *result = (bool *)malloc(p->rows * sizeof(bool));
    bool paddedResult[p->rows][128];

#pragma omp parallel default(none) shared(arr, p, result, paddedResult)
    {
#pragma omp for
        for (int i = 0; i < p->rows; i++)
        {
            result[i] = false;

            int *row = arr[i];
            int size = p->cols[i];

            unsigned long long int combs = 1 << (size - 1);
            unsigned long long int all = ((unsigned long long int)1 << size) - 1;

            int problem_sum = small_sum_par(row, size, all);
            if (problem_sum % 2 != 0)
                continue;
            int half_sum = problem_sum / 2;

            for (int j = 0; j < combs; j++)
            {
                int sum = small_sum_par(row, size, j);
                if (sum == half_sum)
                {
                    result[i] = true;
                    break;
                }
            }
        }
    }

    return result;
}