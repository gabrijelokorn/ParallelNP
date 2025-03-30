#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../kamada_kawai.h"

void get_derivatives_mad(KamadaKawai *kk, int index, double *d_m_x, double *d_m_y, double *d_m_xx, double *d_m_yy, double *d_m_xy)
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
            *d_m_x += addx;
        if (!isnan(addy))
            *d_m_y += addy;
        if (!isnan(addxx))
            *d_m_xx += addxx;
        if (!isnan(addyy))
            *d_m_yy += addyy;
        if (!isnan(addxy))
            *d_m_xy += addxy;
    }
}

int get_deltas_mad(KamadaKawai *kk)
{
    double max_delta = 0.0;

#pragma omp parallel for reduction(max : max_delta)
    for (int i = 0; i < kk->n; i++)
    {
        double temp = get_delta_m(kk, i);
        kk->deltas[i] = temp; // Store the value for later use
        if (temp > max_delta) // Compare instead of overwriting
            max_delta = temp;
    }

    if (max_delta <= kk->epsilon)
        return -1;

    for (int i = 0; i < kk->n; i++)
        if (max_delta == kk->deltas[i])
            return i;

    return -1;
}

void mad(KamadaKawai *kk, Vertices *result)
{
    int delta_max_index = get_deltas_mad(kk);

    while (delta_max_index != -1)
    {
        int steps = kk->limit;
        while (true)
        {
            bool equilibrium = true;

#pragma omp parallel for shared(kk)
            for (int i = 0; i < kk->n; i++)
            {
                double d_x_m = 0, d_y_m = 0, d_xx_m = 0, d_yy_m = 0, d_xy_m = 0;
                get_derivatives_mad(kk, i, &d_x_m, &d_y_m, &d_xx_m, &d_yy_m, &d_xy_m);

                double delta_y = get_delta_m_y(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m);
                double delta_x = get_delta_m_x(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m, delta_y);
                kk->coords[i].x += delta_x;
                kk->coords[i].y += delta_y;

                kk->deltas[i] = get_delta_m(kk, i);
            }

            for (int i = 0; i < kk->n; i++)
                if (kk->deltas[i] > kk->epsilon)
                    equilibrium = false;

            if (equilibrium)
                break;
            if (steps-- <= 0)
                break;
        }

        int temp = get_deltas_mad(kk);
        if (temp == delta_max_index)
            break;
        delta_max_index = temp;
    }

    return;
}