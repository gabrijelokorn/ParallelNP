#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <omp.h>

#include "../kamada_kawai.h"

void get_derivatives_par(KamadaKawai *kk, int index, double *d_m_x, double *d_m_y, double *d_m_xx, double *d_m_yy, double *d_m_xy)
{
    double local_d_x = 0, local_d_y = 0, local_d_xx = 0, local_d_yy = 0, local_d_xy = 0;

    // #pragma omp parallel for reduction(+ : local_d_x, local_d_y, local_d_xx, local_d_yy, local_d_xy)
    for (int i = 0; i < kk->n; i++)
    {
        if (i == index)
            continue;

        double dist_x = kk->coords[index].x - kk->coords[i].x;
        double dist_y = kk->coords[index].y - kk->coords[i].y;
        double x2 = dist_x * dist_x;
        double y2 = dist_y * dist_y;
        double x2_y2 = x2 + y2;
        double x2_y2_1_2 = sqrt(x2_y2);
        double x2_y2_3_2 = pow(x2_y2, 1.5);

        double addend_x = kk->k_ij[index][i] * (dist_x - ((kk->l_ij[index][i] * dist_x) / x2_y2_1_2));
        double addend_y = kk->k_ij[index][i] * (dist_y - ((kk->l_ij[index][i] * dist_y) / x2_y2_1_2));
        double addend_xx = kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * y2) / x2_y2_3_2));
        double addend_yy = kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * x2) / x2_y2_3_2));
        double addend_xy = kk->k_ij[index][i] * ((kk->l_ij[index][i] * dist_x * dist_y) / x2_y2_3_2);

        if (!isnan(addend_x))
            local_d_x += addend_x;
        if (!isnan(addend_y))
            local_d_y += addend_y;
        if (!isnan(addend_xx))
            local_d_xx += addend_xx;
        if (!isnan(addend_yy))
            local_d_yy += addend_yy;
        if (!isnan(addend_xy))
            local_d_xy += addend_xy;
    }

    // Store the accumulated results back into the pointers
    *d_m_x = local_d_x;
    *d_m_y = local_d_y;
    *d_m_xx = local_d_xx;
    *d_m_yy = local_d_yy;
    *d_m_xy = local_d_xy;
}

int get_deltas_par(KamadaKawai *kk)
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

int update_deltas_par(KamadaKawai *kk, int m)
{
    int delta_index = -1;
    double max_delta = 0.0;

#pragma omp parallel for default(none) shared(kk, m, delta_index) reduction(max : max_delta)
    for (int i = 0; i < kk->n; i++)
    {
        if (m == i)
            continue;

        double temp = update_delta_m(kk, m, i);
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

void par(KamadaKawai *kk, Vertices *result)
{
    int delta_max_index = get_deltas_par(kk);

    while (delta_max_index != -1)
    {
        int steps = kk->limit;
        while (kk->deltas[delta_max_index] > kk->epsilon)
        {
            double d_x_m = 0, d_y_m = 0, d_xx_m = 0, d_yy_m = 0, d_xy_m = 0;
            get_derivatives_par(kk, delta_max_index, &d_x_m, &d_y_m, &d_xx_m, &d_yy_m, &d_xy_m);

            double delta_y = get_delta_m_y(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m);
            double delta_x = get_delta_m_x(d_x_m, d_y_m, d_xx_m, d_yy_m, d_xy_m, delta_y);
            kk->coords[delta_max_index].x += delta_x;
            kk->coords[delta_max_index].y += delta_y;

            kk->deltas[delta_max_index] = get_delta_m(kk, delta_max_index);
            if (steps-- <= 0)
                break;
        }

        int temp = update_deltas_par(kk, delta_max_index);
        if (temp == delta_max_index)
            break;
        delta_max_index = temp;
    }

    return;
}