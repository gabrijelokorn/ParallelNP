#ifndef PARTITION_H
#define PARTITION_H

typedef struct Partitions
{
    int quantity;
    int rows;
    int *cols;
} Partitions;

int partition_sum(int *arr, int size, unsigned long long int index);

#endif