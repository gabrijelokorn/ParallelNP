#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <omp.h>

#include "../kamada_kawai.h"

void derivatives_par(KamadaKawai *kk, int index, float *x, float *y, float *xx, float *yy, float *xy)
{
#pragma omp parallel for schedule(static, 1)
    for (int i = 0; i < kk->n; i++)
    {
        if (i == index)
            continue;

        float dist_x = kk->coords[index].x - kk->coords[i].x;
        float dist_y = kk->coords[index].y - kk->coords[i].y;
        float x2 = (float)(dist_x * dist_x);
        float y2 = (float)(dist_y * dist_y);
        float x2_y2 = x2 + y2;
        float x2_y2_1_2 = (float)sqrt(x2_y2);
        float x2_y2_3_2 = (float)pow(x2_y2, (float)3 / 2);

#pragma omp critical
        {
            *x += kk->k_ij[index][i] * (dist_x - ((kk->l_ij[index][i] * dist_x) / x2_y2_1_2));
            *y += kk->k_ij[index][i] * (dist_y - ((kk->l_ij[index][i] * dist_y) / x2_y2_1_2));
            *xx += kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * y2) / x2_y2_3_2));
            *yy += kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * x2) / x2_y2_3_2));
            *xy += kk->k_ij[index][i] * ((kk->l_ij[index][i] * dist_x * dist_y) / x2_y2_3_2);
        }
    }
}

float *get_delatas_par(KamadaKawai *kk)
{
    float *deltas = (float *)malloc(kk->n * sizeof(float));

#pragma omp parallel for shared(deltas)
    for (int i = 0; i < kk->n; i++)
    {
        deltas[i] = get_delta(kk, i);
    }

    return deltas;
}

Vertices *par(KamadaKawai *kk)
{

    Vertices *vertices = (Vertices *)malloc(sizeof(Vertices));
    vertices->coords = (Coord *)malloc(kk->n * sizeof(Coord *));
    copyCoords(kk->coords, vertices->coords, kk->n);

    Vertices *vertices_head = vertices;

    float *deltas = get_delatas_par(kk);
    int delta_max_index = get_delta_max_index(kk, deltas);

    while (delta_max_index != -1)
    {
        while (deltas[delta_max_index] > kk->epsilon)
        {
            float d_x_m = 0;
            float d_y_m = 0;
            float d_xx_m = 0;
            float d_yy_m = 0;
            float d_xy_m = 0;

            derivatives_par(kk, delta_max_index, &d_x_m, &d_y_m, &d_xx_m, &d_yy_m, &d_xy_m);

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

            kk->coords[delta_max_index].x += delta_x;
            kk->coords[delta_max_index].y += delta_y;

            deltas[delta_max_index] = get_delta(kk, delta_max_index);
        }

        deltas = get_delatas_par(kk);
        delta_max_index = get_delta_max_index(kk, deltas);
    }

    vertices->next = (Vertices *)malloc(sizeof(Vertices));
    vertices->next->coords = (Coord *)malloc(kk->n * sizeof(Coord *));
    copyCoords(kk->coords, vertices->next->coords, kk->n);
    vertices = vertices->next;
    vertices->next = NULL;

    return vertices_head;
}