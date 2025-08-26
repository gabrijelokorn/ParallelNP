#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

#include "./kamada_kawai2csv.h"

void writeState(FILE *fp, Coord *state, int n)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%f,%f\n", state[i].x, state[i].y);
    }
    fprintf(fp, "\n");
}