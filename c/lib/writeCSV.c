#include "writeCSV.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void writeVertices(FILE *fp, Vertices *vertices, int n)
{
    if (fp == NULL) {
        fprintf(stderr, ")-: File pointer is null\n");
        return;
    }

    while (vertices != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(fp, "%f,%f\n", vertices->coordinates[i][0], vertices->coordinates[i][1]);
        }
        vertices = vertices->next;
        fprintf(fp, "\n");
    }
}