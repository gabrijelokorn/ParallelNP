#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../kamada_kawai.h"

void get_derivatives_seq(KamadaKawai *kk, int index, double *d_m_x, double *d_m_y, double *d_m_xx, double *d_m_yy, double *d_m_xy)
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

int get_deltas_seq(KamadaKawai *kk)
{
    int delta_index = -1;
    double max_delta = 0.0;

    for (int i = 0; i < kk->n; i++)
    {
        kk->deltas[i] = get_delta_m(kk, i);

        if (kk->deltas[i] > kk->epsilon)
        {
            if (kk->deltas[i] > max_delta)
            {
                max_delta = kk->deltas[i];
                delta_index = i;
            }
        }
    }

    return delta_index;
}

int update_deltas_seq(KamadaKawai *kk, int m)
{
    int delta_index = -1;
    double max_delta = 0.0;

    for (int i = 0; i < kk->n; i++)
    {
        if (m == i)
            continue;

        kk->deltas[i] = update_delta_m(kk, m, i);

        if (kk->deltas[i] > kk->epsilon)
        {
            if (kk->deltas[i] > max_delta)
            {
                max_delta = kk->deltas[i];
                delta_index = i;
            }
        }
    }

    return delta_index;
}

void seq(KamadaKawai *kk, Vertices *result)
{
    int delta_max_index = get_deltas_seq(kk);

    while (delta_max_index != -1)
    {
        int steps = kk->limit;
        while (kk->deltas[delta_max_index] > kk->epsilon)
        {
            double d_x_m = 0, d_y_m = 0, d_xx_m = 0, d_yy_m = 0, d_xy_m = 0;
            get_derivatives_seq(kk, delta_max_index, &d_x_m, &d_y_m, &d_xx_m, &d_yy_m, &d_xy_m);

            double delta_y = get_delta_m_y(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m);
            double delta_x = get_delta_m_x(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m, delta_y);
            kk->coords[delta_max_index].x += delta_x;
            kk->coords[delta_max_index].y += delta_y;

            kk->deltas[delta_max_index] = get_delta_m(kk, delta_max_index);

            if (steps-- <= 0)
                break;
        }

        int temp = update_deltas_seq(kk, delta_max_index);
        if (temp == delta_max_index)
            break;
        delta_max_index = temp;
    }

    return;
}