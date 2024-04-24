#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile (char *argv[], int **arr, int *size) {
    // if (debug) {
    //     // Pointer (value is the address of the array)
    //     printf("size: %p\n", size);
    //     // Address where the pointer is stored
    //     printf("&size: %p\n", &size);
    //     // Value of where the pointer size is pointing to
    //     printf("*size: %d\n", *size);
    // }

    // Open the file with test cases
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: File not found\n");
        exit(1);
    }

    char* line = NULL;
    size_t line_length = 0;

    // Count elements seperated by the delimiter ','
    while (getline(&line, &line_length, file) != -1) {
        char *token = strtok(line, ",");
        while (token != NULL) {
            (*size)++;
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
            (*arr)[i++] = atoi(token);
            token = strtok(NULL, ",");
        }
    }

    // Close the file
    fclose(file);
    free(line);
}