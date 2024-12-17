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
    unsigned long long int possibilities = 1 << (size - 1);
    unsigned long long int complete_set = ((unsigned long long int)1 << size) - 1;
    
    int problem_sum = large_sum_seq(arr, size, complete_set);
    if (problem_sum % 2 != 0)
        return false;
    int half_problem_sum = problem_sum / 2;

    for (int i = 0; i < possibilities; i++)
    {
        int sum = large_sum_seq(arr, size, i);
        if (sum == half_problem_sum)
            return true;
    }

    return false;
}