#include "readFile.h"

char *readFile(FILE *fp)
{
    // 1. Determine input file size
    fseek(fp, 0, SEEK_END);     // Move the cursor to the end of the file
    int size = getFileSize(fp); // Get the position of the cursor
    rewind(fp);                 // Move the cursor to the beginning of the file

    // 2. Allocate memory for the file
    char *buffer = (char *)malloc((size + 1) * sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr, "%s )-: Error allocating memory\n", "lib/readFile.c");
        fclose(fp);
        return NULL;
    }

    // 3. Read the file into a buffer
    fread(buffer, size, 1, fp);
    // Null terminate the buffer
    buffer[size] = '\0';

    return buffer;
}