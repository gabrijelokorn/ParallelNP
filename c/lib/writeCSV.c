#include "writeCSV.h"

void writeEdges(FILE *fp, int **edges, int m)
{
    for (int i = 0; i < m; i++)
    {
        fprintf(fp, "%d,%d\n", edges[i][0], edges[i][1]);
    }
}

void writePoints(FILE *fp, int n)
{
    fprintf(fp, "%d\n", n);
}