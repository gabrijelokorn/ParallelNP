#include "read.h"

int readLine(FILE *file, int *arr)
{
    int numOfElements = 0 ;
    char *line = NULL;
    size_t line_length = 0;

    // Read the elements from the file to array
    int i = 0;
    getline(&line, &line_length, file);
    char *token = strtok(line, ",");
    while (token != NULL)
    {
        int num = atoi(token);
        if (!num == 0)
            numOfElements++;
            arr[i++] = num;
        token = strtok(NULL, ",");
    }

    // Free the allocated string
    free(line);
    return numOfElements;
}

int countNumbers(FILE *file)
{
    int size = 0;
    char *line = NULL;
    size_t line_length = 0;

    // Count elements seperated by the delimiter ','
    getline(&line, &line_length, file);
    char *token = strtok(line, ",");
    while (token != NULL)
    {
        int num = atoi(token);
        size++;
        token = strtok(NULL, ",");
    }

    // Free the allocated string
    free(line);
    return size;
}

int countLines(FILE *file)
{
    int lines = 0;
    fseek(file, 0, SEEK_SET);
    char *line = NULL;
    size_t line_length = 0;

    // Count elements seperated by the delimiter ','
    while (getline(&line, &line_length, file) != -1)
    {
        lines++;
    }

    // Free the allocated string
    free(line);

    return lines;
}

void read1d(char *argv[], int** arr, int* size)
{
    FILE *file = fopen(argv[1], "r");

    int lines = countLines(file);

    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < lines; i++)
    {
        *size += countNumbers(file);
    }


    *arr = (int *)malloc(*size * sizeof(int));

    int numOfElements = 0;
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < lines; i++)
    {
        numOfElements += readLine(file, (*arr) + numOfElements);
    }

    fclose(file);
    return;
}

void read2d(char *argv[], int ***arr, int **size, int* lines)
{
    FILE *file = fopen(argv[1], "r");

    *lines = countLines(file);
    *size = (int *)malloc(*lines * sizeof(int));
    *arr = (int **)malloc(*lines * sizeof(int *));

    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < *lines; i++)
    {
        (*size)[i] = countNumbers(file);
        (*arr)[i] = (int *)malloc((*size)[i] * sizeof(int));
    }

    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < *lines; i++)
    {
        readLine(file, (*arr)[i]);
    }


    fclose(file);
    return;
}