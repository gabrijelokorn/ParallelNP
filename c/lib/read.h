#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read1d(char *argv[], int **arr, int *size);
void read2d(char* argv[], int*** arr, int** size, int* lines);

#endif