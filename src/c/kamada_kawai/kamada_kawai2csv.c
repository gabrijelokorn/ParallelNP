#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

#include "./kamada_kawai2csv.h"

void writeVertices(Vertices *vertices, int n, char *resultFile)
{
    FILE *fp = fopen(resultFile, "w");
    while (vertices != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(fp, "%f,%f\n", vertices->coords[i].x, vertices->coords[i].y);
        }
        vertices = vertices->next;
        fprintf(fp, "\n");
    }
    fclose(fp);
}