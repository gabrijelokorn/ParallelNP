#include <omp.h>

#include "large.h"

int set_sum_par(int *arr, int size, unsigned long long int index)
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

bool par(int *arr, int size)
{
    unsigned long long int possibilities = 1 << (size - 1);

    int total_sum = set_sum_par(arr, size, (1 << (size)) - 1);
    int half_sum = total_sum / 2;
    if (total_sum % 2 != 0)
        return false;

    bool found = false;
    printf("cancel %d\n", omp_get_cancellation());

#pragma omp teams distribute parallel for shared(found)
    for (int i = 0; i < possibilities; i++)
    {
        printf("Thread %d from team: %d testing possibility: %d\n", omp_get_thread_num(), omp_get_team_num(), i);
        int sum = set_sum_par(arr, size, i);
        if (sum == half_sum)
        {
            // printf("--------------- The thread %d from team %d found the solution: %d\n", omp_get_thread_num(), omp_get_team_num(), sum);
            found = true;
        }
    }

    return found;
}