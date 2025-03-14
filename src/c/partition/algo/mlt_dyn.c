#include <stdbool.h>

#include "algo.h"

int sum_mlt_dyn(int *arr, int size, unsigned long long int index)
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

bool *mlt_dyn(Partitions *p, int **arr)
{
    bool *result = (bool *)malloc(p->rows * sizeof(bool));

    {
#pragma omp parallel default(none) shared(arr, p, result)
#pragma omp for schedule(dynamic, 5)
        for (int i = 0; i < p->rows; i++)
        {
            result[i] = false;

            int *row = arr[i];
            int size = p->cols[i];

            unsigned long long int combs = 1 << (size - 1);
            unsigned long long int all = ((unsigned long long int)1 << size) - 1;

            int problem_sum = sum_mlt_dyn(row, size, all);
            if (problem_sum % 2 != 0)
                continue;
            int half_sum = problem_sum / 2;

            for (int j = 0; j < combs; j++)
            {
                int sum = sum_mlt_dyn(row, size, j);
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