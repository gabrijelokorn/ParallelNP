#ifndef WRITECSV_H
#define WRITECSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeEdges(FILE *fp, int **edges, int m);
void writePoints(FILE *fp, int n);

#endif