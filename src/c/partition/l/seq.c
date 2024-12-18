#include "large.h"

int large_sum_seq(int *arr, int size, unsigned long long int index)
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

bool large_seq(int *arr, int size)
{
    unsigned long long int combs = 1 << (size - 1);
    unsigned long long int all = ((unsigned long long int)1 << size) - 1;
    
    int problem_sum = large_sum_seq(arr, size, all);
    if (problem_sum % 2 != 0)
        return false;
    int half_sum = problem_sum / 2;

    for (int i = 0; i < combs; i++)
    {
        int sum = large_sum_seq(arr, size, i);
        if (sum == half_sum)
            return true;
    }

    return false;
}