#include <stdio.h>

void printArray(int *arr, int size)
{
    printf("|> Elements: [");
    for (int i = 0; i < size; i++)
    {
        if (i != 0)
        {
            printf(", ");
        }
        printf("%d", arr[i]);
    }
    printf("]\n");

    return;
}