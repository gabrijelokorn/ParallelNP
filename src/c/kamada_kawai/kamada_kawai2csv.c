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
            fprintf(fp, "%f,%f\n", vertices->coords[i].x, vertices->coords[i].y);
        }
        vertices = vertices->next;
        fprintf(fp, "\n");
    }
}