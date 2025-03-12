#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

FILE *openFile(char *filename, char *mode);
char *generateFilename(char *algo, char *out, char *ext);

#endif