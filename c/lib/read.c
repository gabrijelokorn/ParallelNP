#include "read.h"

void readNumbers(FILE *file, int *arr, int size)
{
    fseek(file, 0, SEEK_SET);
    char *line = NULL;
    size_t line_length = 0;

    // Read the elements from the file to array
    int i = 0;
    while (getline(&line, &line_length, file) != -1)
    {
        char *token = strtok(line, ",");
        while (token != NULL)
        {
            int num = atoi(token);
            if (!num == 0)
                arr[i++] = num;
            token = strtok(NULL, ",");
        }
    }

    // Free the allocated string
    free(line);
    return;
}

// int countNumbers(FILE *file)
// {
//     fseek(file, 0, SEEK_SET);
//     int size = 0;
//     char *line = NULL;
//     size_t line_length = 0;

//     // Count elements seperated by the delimiter ','
//     while (getline(&line, &line_length, file) != -1)
//     {
//         char *token = strtok(line, ",");
//         while (token != NULL)
//         {
//             int num = atoi(token);
//             if (!num == 0)
//                 (size)++;
//             token = strtok(NULL, ",");
//         }
//     }

//     // Free the allocated string
//     free(line);

//     return size;
// }

void readFile(char *argv[], int **arr, int *size)
{
    // Open the file with test cases
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("[read.c]: File %s not found\n", argv[1]);
        exit(1);
    }

    *size = countNumbers(file);
    *arr = (int *)malloc(*size * sizeof(int));
    if (*arr == NULL)
    {
        printf("[read.c]: Memory allocation failed\n");
        exit(1);
    }
    
    readNumbers(file, *arr, *size);

    // Close the file
    fclose(file);

    return;
}

int countNumbers (FILE *file) {
    int size = 0;
    fseek(file, 0, SEEK_SET);

    char *line = NULL;
    size_t line_length = 0;

    // Count elements seperated by the delimiter ','
    while (getline(&line, &line_length, file) != -1)
    {
        char *token = strtok(line, ",");
        while (token != NULL)
        {
            int num = atoi(token);
            if (!num == 0)
                size++;
            token = strtok(NULL, ",");
        }
    }

    // Free the allocated string
    free(line);
    return size;
}

int countLines (FILE *file) {
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

void read2d(char* argv[], int*** arr, int** size) {
    FILE* file = fopen(argv[1], "r");

    int lines = countLines(file);
    *size = (int *)malloc(lines * sizeof(int));
    *arr = (int **)malloc(lines * sizeof(int*));

    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < lines; i++) {
        (*size)[i] = countNumbers(file);
        (*arr)[i] = (int *)malloc((*size)[i] * sizeof(int));
        countNumbers(file);
    }

    fclose(file);
    return;
}