#include "./kamada_kawai.h"

void copyCoords(Coord *kk_coords, Coord *v_coords, int n)
{
    for (int i = 0; i < n; i++)
    {
        v_coords[i].x = kk_coords[i].x;
        v_coords[i].y = kk_coords[i].y;
    }
}