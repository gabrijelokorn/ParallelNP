/**
 * @file partition_iter.c
 * @author Gabrijel Okorn (gabrijel.okorn@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "read.h"

bool debug = true;

int main (int argc, char *argv[]) {
    int size = 0;
    int *arr = NULL;

    readFile(argv, &arr, &size);

    if (debug)  {
        printf("|> # elements: %d\n", size);

        bool first = true;
        printf("|> Elements: [");
        for (int i = 0; i < size; i++) {
            if (!first) {
                printf(", ", arr[i]);
            } else {
                first = false;
            }
            printf("%d", arr[i]);
        }
        printf("]\n");
    }



    return 0;
}