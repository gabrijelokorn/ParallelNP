#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "./kamada_kawai.h"

void copyCoords(Coord *kk_coords, Coord *v_coords, int n)
{
    for (int i = 0; i < n; i++)
    {
        v_coords[i].x = kk_coords[i].x;
        v_coords[i].y = kk_coords[i].y;
    }
}

double get_delta_m_y(double d_m_x, double d_m_y, double d_m_xx, double d_m_yy, double d_m_xy)
{
    return (-(d_m_xy * d_m_x) + (d_m_xx * d_m_y)) / (-(d_m_xx * d_m_yy) + (d_m_xy * d_m_xy));
}
double get_delta_m_x(double d_m_x, double d_m_y, double d_m_xx, double d_m_yy, double d_m_xy, double delta_y)
{
    return (-(d_m_y) - (d_m_yy * delta_y)) / d_m_xy;
}

double get_derivative_x(KamadaKawai *kk, int index)
{
    double sum = 0;

    for (int i = 0; i < kk->n; i++)
    {
        if (i == index)
        {
            kk->addendx[index][i] = 0;
            continue;
        }

        double dist_x = kk->coords[index].x - kk->coords[i].x;
        double dist_y = kk->coords[index].y - kk->coords[i].y;

        double addend = kk->k_ij[index][i] * (dist_x - ((kk->l_ij[index][i] * dist_x) / (double)sqrt((double)pow(dist_x, 2) + (double)pow(dist_y, 2))));
        if (isnan(addend))
            continue;

        kk->addendx[index][i] = addend;
        sum += addend;
    }

    kk->dx[index] = sum;
    return sum;
}
double get_derivative_y(KamadaKawai *kk, int index)
{
    double sum = 0;

    for (int i = 0; i < kk->n; i++)
    {
        if (i == index)
        {
            kk->addendy[index][i] = 0;
            continue;
        }

        double dist_x = kk->coords[index].x - kk->coords[i].x;
        double dist_y = kk->coords[index].y - kk->coords[i].y;

        double addend = kk->k_ij[index][i] * (dist_y - ((kk->l_ij[index][i] * dist_y) / (double)sqrt((double)pow(dist_x, 2) + (double)pow(dist_y, 2))));

        if (isnan(addend))
            continue;

        kk->addendy[index][i] = addend;
        sum += addend;
    }

    kk->dy[index] = sum;
    return sum;
}

double get_delta_m(KamadaKawai *kk, int index)
{
    return sqrt((double)pow(get_derivative_x(kk, index), 2) + (double)pow(get_derivative_y(kk, index), 2));
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

double get_addend_x(KamadaKawai *kk, int m, int index)
{
    double dist_x = kk->coords[index].x - kk->coords[m].x;
    double dist_y = kk->coords[index].y - kk->coords[m].y;

    double addend = kk->k_ij[index][m] * (dist_x - ((kk->l_ij[index][m] * dist_x) / (double)sqrt((double)pow(dist_x, 2) + (double)pow(dist_y, 2))));
    if (isnan(addend))
        return 0;

    return addend;
}
double get_addend_y(KamadaKawai *kk, int m, int index)
{
    double dist_x = kk->coords[index].x - kk->coords[m].x;
    double dist_y = kk->coords[index].y - kk->coords[m].y;

    double addend = kk->k_ij[index][m] * (dist_y - ((kk->l_ij[index][m] * dist_y) / (double)sqrt((double)pow(dist_x, 2) + (double)pow(dist_y, 2))));

    if (isnan(addend))
        return 0;

    return addend;
}

double update_delta_m(KamadaKawai *kk, int m, int index)
{
    double tempx = get_addend_x(kk, m, index);
    double tempy = get_addend_y(kk, m, index);

    kk->dx[index] = kk->dx[index] - kk->addendx[index][m] + tempx;
    kk->dy[index] = kk->dy[index] - kk->addendy[index][m] + tempy;

    kk->addendx[index][m] = tempx;
    kk->addendy[index][m] = tempy;

    return sqrt((double)pow(kk->dx[index], 2) + (double)pow(kk->dy[index], 2));
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
void get_derivatives_par(KamadaKawai *kk, int index, double *d_m_x, double *d_m_y, double *d_m_xx, double *d_m_yy, double *d_m_xy)
{
    double local_d_x = 0, local_d_y = 0, local_d_xx = 0, local_d_yy = 0, local_d_xy = 0;

#pragma omp parallel for reduction(+ : local_d_x, local_d_y, local_d_xx, local_d_yy, local_d_xy)
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

    *d_m_x = local_d_x;
    *d_m_y = local_d_y;
    *d_m_xx = local_d_xx;
    *d_m_yy = local_d_yy;
    *d_m_xy = local_d_xy;
}