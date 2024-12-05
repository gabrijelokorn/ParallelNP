#include "large.h"

int seq_sum(int *arr, int size, unsigned long long int index)
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

bool seq(int *arr, int size)
{
    unsigned long long int possibilities = 1 << (size - 1);
    unsigned long long int complete_set = ((unsigned long long int)1 << size) - 1;
    
    int total_sum = seq_sum(arr, size, complete_set);
    if (total_sum % 2 != 0)
        return false;
    int half_sum = total_sum / 2;

    for (int i = 0; i < possibilities; i++)
    {
        int sum = seq_sum(arr, size, i);
        if (sum == half_sum)
            return true;
    }

    return false;
}