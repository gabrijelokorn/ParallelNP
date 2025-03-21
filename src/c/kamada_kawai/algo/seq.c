#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../kamada_kawai.h"

void derivatives_seq(KamadaKawai *kk, int index, double *x, double *y, double *xx, double *yy, double *xy)
{
    for (int i = 0; i < kk->n; i++)
    {
        if (i == index)
            continue;

        double dist_x = kk->coords[index].x - kk->coords[i].x;
        double dist_y = kk->coords[index].y - kk->coords[i].y;
        double x2 = (double)pow(dist_x, 2);
        double y2 = (double)pow(dist_y, 2);
        double x2_y2 = x2 + y2;
        double x2_y2_1_2 = (double)sqrt(x2_y2);
        double x2_y2_3_2 = (double)pow(x2_y2, (double)3 / 2);

        double addx = kk->k_ij[index][i] * (dist_x - ((kk->l_ij[index][i] * dist_x) / x2_y2_1_2));
        double addy = kk->k_ij[index][i] * (dist_y - ((kk->l_ij[index][i] * dist_y) / x2_y2_1_2));
        double addxx = kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * y2) / x2_y2_3_2));
        double addyy = kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * x2) / x2_y2_3_2));
        double addxy = kk->k_ij[index][i] * ((kk->l_ij[index][i] * dist_x * dist_y) / x2_y2_3_2);

        if (!isnan(addx))
            *x += addx;
        if (!isnan(addy))
            *y += addy;
        if (!isnan(addxx))
            *xx += addxx;
        if (!isnan(addyy))
            *yy += addyy;
        if (!isnan(addxy))
            *xy += addxy;
    }
}

Vertices *seq(KamadaKawai *kk)
{
    Vertices *vertices = (Vertices *)malloc(sizeof(Vertices));
    vertices->coords = (Coord *)malloc(kk->n * sizeof(Coord));
    copyCoords(kk->coords, vertices->coords, kk->n);
    Vertices *vertices_head = vertices;

    double *deltas = get_delatas(kk);
    int delta_max_index = get_delta_max_index(kk, deltas);

    int iter = 0;
    while (delta_max_index != -1)
    {
        printf("iter: %d\n", iter++);
        while (deltas[delta_max_index] > kk->epsilon)
        {
            // double d_x_m = derivaitve_x_m(kk, delta_max_index);
            // double d_y_m = derivaitve_y_m(kk, delta_max_index);
            // double d_xx_m = derivaitve_xx_m(kk, delta_max_index);
            // double d_yy_m = derivaitve_yy_m(kk, delta_max_index);
            // double d_xy_m = derivaitve_xy_m(kk, delta_max_index);
            double d_x_m = 0;
            double d_y_m = 0;
            double d_xx_m = 0;
            double d_yy_m = 0;
            double d_xy_m = 0;

            derivatives_seq(kk, delta_max_index, &d_x_m, &d_y_m, &d_xx_m, &d_yy_m, &d_xy_m);

            double delta_y = get_delta_y(
                d_x_m,
                d_y_m,
                d_xx_m,
                d_yy_m,
                d_xy_m);

            double delta_x = get_delta_x(
                d_x_m,
                d_y_m,
                d_xx_m,
                d_yy_m,
                d_xy_m,
                delta_y);

            kk->coords[delta_max_index].x += delta_x;
            kk->coords[delta_max_index].y += delta_y;
            
            deltas[delta_max_index] = get_delta(kk, delta_max_index);
        }

        deltas = get_delatas(kk);
        delta_max_index = get_delta_max_index(kk, deltas);
    }

    vertices->next = (Vertices *)malloc(sizeof(Vertices));
    vertices->next->coords = (Coord *)malloc(kk->n * sizeof(Coord));
    copyCoords(kk->coords, vertices->next->coords, kk->n);
    vertices = vertices->next;
    vertices->next = NULL;

    return vertices_head;
}