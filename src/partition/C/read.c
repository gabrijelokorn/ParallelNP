#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile (char *argv[], int **arr, int *size) {
    // Open the file with test cases
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: File %s not found\n", argv[1]);
        return 1;
    }

    char* line = NULL;
    size_t line_length = 0;

    // Count elements seperated by the delimiter ','
    while (getline(&line, &line_length, file) != -1) {
        char *token = strtok(line, ",");
        while (token != NULL) {
            if (!atoi(token) == 0) (*size)++;
            token = strtok(NULL, ",");
        }
    }

    // Allocate memory for the array
    *arr = (int *) malloc(*size * sizeof(int));

    // Read the elements from the file to array
    fseek(file, 0, SEEK_SET);
    int i = 0;
    while (getline(&line, &line_length, file) != -1) {
        char *token = strtok(line, ",");
        while (token != NULL) {
            if (!atoi(token) == 0) (*arr)[i++] = atoi(token);
            token = strtok(NULL, ",");
        }
    }

    // Close the file
    fclose(file);
    // Free the allocated string
    free(line);
}