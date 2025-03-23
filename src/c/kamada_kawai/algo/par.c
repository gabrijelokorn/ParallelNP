#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <omp.h>

#include "../kamada_kawai.h"

void derivatives_par(KamadaKawai *kk, int index, double *x, double *y, double *xx, double *yy, double *xy)
{
#pragma omp parallel for schedule(static, 1)
    for (int i = 0; i < kk->n; i++)
    {
        if (i == index)
            continue;

        double dist_x = kk->coords[index].x - kk->coords[i].x;
        double dist_y = kk->coords[index].y - kk->coords[i].y;
        double x2 = (double)(dist_x * dist_x);
        double y2 = (double)(dist_y * dist_y);
        double x2_y2 = x2 + y2;
        double x2_y2_1_2 = (double)sqrt(x2_y2);
        double x2_y2_3_2 = (double)pow(x2_y2, (double)3 / 2);

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

double *get_delatas_par(KamadaKawai *kk)
{
    double *deltas = (double *)malloc(kk->n * sizeof(double));

#pragma omp parallel for shared(deltas)
    for (int i = 0; i < kk->n; i++)
    {
        deltas[i] = get_delta(kk, i);
    }

    return deltas;
}

Vertices *par(KamadaKawai *kk)
{
    // Create sturct to store results of program execution
    Vertices *result = (Vertices *)malloc(sizeof(Vertices));
    result->coords = (Coord *)malloc(kk->n * sizeof(Coord));

    // Copy the coordiantes of original problem into result struct
    copyCoords(kk->coords, result->coords, kk->n);

    Vertices *result_head = result;

    // deltas - array: stores the value of delta for each particle
    double *deltas = get_delatas_par(kk);
    // delta_max_index - index of the particle with highest delta value
    int delta_max_index = get_delta_max_index(kk, deltas);

    while (delta_max_index != -1)
    {
        while (deltas[delta_max_index] > kk->epsilon)
        {
            double d_x_m = 0;
            double d_y_m = 0;
            double d_xx_m = 0;
            double d_yy_m = 0;
            double d_xy_m = 0;

            derivatives_par(kk, delta_max_index, &d_x_m, &d_y_m, &d_xx_m, &d_yy_m, &d_xy_m);

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

        deltas = get_delatas_par(kk);
        delta_max_index = get_delta_max_index(kk, deltas);
    }
    
    // Copy the resulting coordinates to the resulting struct
    result->next = (Vertices *)malloc(sizeof(Vertices));
    result->next->coords = (Coord *)malloc(kk->n * sizeof(Coord));
    copyCoords(kk->coords, result->next->coords, kk->n);

    // Mark the resulting coordinates as last
    result = result->next;
    result->next = NULL;

    return result_head;
}