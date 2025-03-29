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

double get_delta_m_y(double d_m_x, double d_m_y, double d_m_xx, double d_m_yy, double d_m_xy)
{
    return (-(d_m_xy * d_m_x) + (d_m_xx * d_m_y)) / (-(d_m_xx * d_m_yy) + (d_m_xy * d_m_xy));
}

double get_delta_m_x(double d_m_x, double d_m_y, double d_m_xx, double d_m_yy, double d_m_xy, double delta_y)
{
    return (-(d_m_y) - (d_m_yy * delta_y)) / d_m_xy;
}

double get_delta_m(KamadaKawai *kk, int index)
{
    return sqrt((double)pow(get_derivative_x(kk, index), 2) + (double)pow(get_derivative_y(kk, index), 2));
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
