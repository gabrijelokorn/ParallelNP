#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../kamada_kawai.h"

void derivatives_seq(KamadaKawai *kk, int index, float *x, float *y, float *xx, float *yy, float *xy)
{
    for (int i = 0; i < kk->n; i++)
    {
        if (i == index)
            continue;

        float dist_x = kk->coords[index].x - kk->coords[i].x;
        float dist_y = kk->coords[index].y - kk->coords[i].y;
        float x2 = (float)pow(dist_x, 2);
        float y2 = (float)pow(dist_y, 2);
        float x2_y2 = x2 + y2;
        float x2_y2_1_2 = (float)sqrt(x2_y2);
        float x2_y2_3_2 = (float)pow(x2_y2, (float)3 / 2);

        *x += kk->k_ij[index][i] * (dist_x - ((kk->l_ij[index][i] * dist_x) / x2_y2_1_2));
        *y += kk->k_ij[index][i] * (dist_y - ((kk->l_ij[index][i] * dist_y) / x2_y2_1_2));
        *xx += kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * y2) / x2_y2_3_2));
        *yy += kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * x2) / x2_y2_3_2));
        *xy += kk->k_ij[index][i] * ((kk->l_ij[index][i] * dist_x * dist_y) / x2_y2_3_2);
    }
}

Vertices *seq(KamadaKawai *kk)
{
    printf("------------------------new problem\n");
    Vertices *vertices = (Vertices *)malloc(sizeof(Vertices));
    vertices->coords = (Coord *)malloc(kk->n * sizeof(Coord *));
    copyCoords(kk->coords, vertices->coords, kk->n);
    Vertices *vertices_head = vertices;

    float *deltas = get_delatas(kk);
    int delta_max_index = get_delta_max_index(kk, deltas);

    int iter = 0;
    while (delta_max_index != -1)
    {
        int allowed = 1000;
        printf("----------iter: %d\n", iter++);
        while (deltas[delta_max_index] > kk->epsilon)
        {
            // printf("delta_max_index: %d\n", delta_max_index);
            float d_x_m = derivaitve_x_m(kk, delta_max_index);
            float d_y_m = derivaitve_y_m(kk, delta_max_index);
            float d_xx_m = derivaitve_xx_m(kk, delta_max_index);
            float d_yy_m = derivaitve_yy_m(kk, delta_max_index);
            float d_xy_m = derivaitve_xy_m(kk, delta_max_index);
            // float d_x_m = 0;
            // float d_y_m = 0;
            // float d_xx_m = 0;
            // float d_yy_m = 0;
            // float d_xy_m = 0;

            // derivatives_seq(kk, delta_max_index, &d_x_m, &d_y_m, &d_xx_m, &d_yy_m, &d_xy_m);

            float delta_y = get_delta_y(
                d_x_m,
                d_y_m,
                d_xx_m,
                d_yy_m,
                d_xy_m);

            float delta_x = get_delta_x(
                d_x_m,
                d_y_m,
                d_xx_m,
                d_yy_m,
                d_xy_m,
                delta_y);

            // printf("before moving: x: %.15f, y: %.15f ||| delatax: %.15f, deltay: %.15f\n", kk->coords[delta_max_index].x, kk->coords[delta_max_index].y, delta_x, delta_y);
            kk->coords[delta_max_index].x += delta_x;
            kk->coords[delta_max_index].y += delta_y;

            if (allowed <= 0)
            {
                // allowed = 500;
                // print all the points:
                //  for (int i = 0; i < kk->n; i++)
                //  {
                //      printf("Point %d: x: %.15f, y: %.15f\n", i, kk->coords[i].x, kk->coords[i].y);
                //  }
                //  exit(1);
                // double testing = (double)delta_x;
                // float sum1 = kk->coords[delta_max_index].x + delta_x;
                // double sum2 = (double)kk->coords[delta_max_index].x + (double)delta_x;
                // printf("float sum: %.15f, double sum: %.15f\n", sum1, sum2);
                // exit(1);
            }

            deltas[delta_max_index] = get_delta(kk, delta_max_index);
            allowed--;
        }

        deltas = get_delatas(kk);
        delta_max_index = get_delta_max_index(kk, deltas);
    }

    vertices->next = (Vertices *)malloc(sizeof(Vertices));
    vertices->next->coords = (Coord *)malloc(kk->n * sizeof(Coord *));
    copyCoords(kk->coords, vertices->next->coords, kk->n);
    vertices = vertices->next;
    vertices->next = NULL;

    return vertices_head;
}