#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

#include "./kamada_kawai2csv.h"

void writeVertices(FILE *fp, Vertices *vertices, int n)
{
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