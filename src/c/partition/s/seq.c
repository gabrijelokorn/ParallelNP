#include <stdbool.h>

#include "small.h"

int small_sum_seq(int *arr, int size, unsigned long long int index)
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

bool *small_seq(int **arr, Partitions *p)
{
    bool *result = (bool *)malloc(p->rows * sizeof(bool));

    for (int i = 0; i < p->rows; i++)
    {
        result[i] = false;

        int *row = arr[i];
        int size = p->cols[i];

        unsigned long long int possibilities = 1 << (size - 1);
        unsigned long long int complete_set = ((unsigned long long int)1 << size) - 1;

        int total_sum = small_sum_seq(row, size, complete_set);
        if (total_sum % 2 != 0)
            continue;
        int half_problem_sum = total_sum / 2;

        for (int j = 0; j < possibilities; j++)
        {
            int sum = small_sum_seq(row, size, j);
            if (sum == half_problem_sum)
            {
                result[i] = true;
                break;
            }
        }
    }

    return result;
}