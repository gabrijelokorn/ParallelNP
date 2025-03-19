#include <stdbool.h>

#include "algo.h"

int sum_sgl_dyn(int *arr, int size, unsigned long long int index)
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

bool *sgl_dyn(Partitions *p, int **arr)
{
    bool *result = (bool *)malloc(p->rows * sizeof(bool));

    for (int i = 0; i < p->rows; i++)
    {
        result[i] = false;

        int *row = arr[i];
        int size = p->cols[i];

        unsigned long long int numOfCombinations = 1 << (size - 1);
        unsigned long long int allNumbersMask = ((unsigned long long int)1 << size) - 1;

        int problem_sum = sum_sgl_dyn(row, size, allNumbersMask);
        if (problem_sum % 2 != 0)
            continue;
        int half_sum = problem_sum / 2;

        {
            bool found = false;
            #pragma omp parallel default(none) shared(row, size, numOfCombinations, half_sum, result, i, found)
            #pragma omp for schedule(dynamic, 10)
            for (int j = 0; j < numOfCombinations; j++)
            {
                if (found)
                    continue;
                int sum = sum_sgl_dyn(row, size, j);
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