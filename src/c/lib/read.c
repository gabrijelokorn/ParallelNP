#include <stdio.h>
#include <string.h>

#include "read.h"

int getFileSize (FILE *fp)
{
    int size = 0;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    return size;
}

char *readFile(char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "%s )-: File pointer is null\n", "readFile");
        return NULL;
    }
    // 1. Determine input file size
    fseek(fp, 0, SEEK_END);     // Move the cursor to the end of the file
    int size = getFileSize(fp); // Get the position of the cursor
    rewind(fp);                 // Move the cursor to the beginning of the file

    // 2. Allocate memory for the file
    char *buffer = (char *)malloc((size + 1) * sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr, "%s )-: Error allocating memory\n", "readFile");
        fclose(fp);
        return NULL;
    }

    // 3. Read the file into a buffer
    fread(buffer, size, 1, fp);
    // Null terminate the buffer
    buffer[size] = '\0';

    fclose(fp);
    return buffer;
}