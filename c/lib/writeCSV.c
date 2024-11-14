#include "writeCSV.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeVertices(FILE *fp, Vertices *vertices, int n)
{
    if (fp == NULL)
    {
        fprintf(stderr, ")-: File pointer is null\n");
        return;
    }

    Vertices *temp = vertices;
    int frames = 0;
    while (temp != NULL)
    {
        frames++;
        temp = temp->next;
    }

    int freq = frames / 3;
    if (freq == 0)
        freq = 1;

    int count = 0;
    while (vertices != NULL)
    {
        count++;
        if (count % freq != 0 && 
        count != 0 && 
        count != 1 && 
        count != 2 &&
        count != frames)
        {
            vertices = vertices->next;
            continue;
        }
        for (int i = 0; i < n; i++)
        {
            fprintf(fp, "%f,%f\n", vertices->coordinates[i][0], vertices->coordinates[i][1]);
        }
        vertices = vertices->next;
        fprintf(fp, "\n");
    }
}