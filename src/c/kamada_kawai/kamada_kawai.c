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

double derivaitve_x_m(KamadaKawai *kk, int index)
{
    double sum = 0;

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

        double additive = kk->k_ij[index][i] * (dist_x - ((kk->l_ij[index][i] * dist_x) / x2_y2_1_2));
        if (isnan(additive))
            continue;

        sum += additive;
    }

    return sum;
}

double derivaitve_y_m(KamadaKawai *kk, int index)
{
    double sum = 0;

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

        double additive = kk->k_ij[index][i] * (dist_y - ((kk->l_ij[index][i] * dist_y) / x2_y2_1_2));

        if (isnan(additive))
            continue;

        sum += additive;
    }

    return sum;
}

double derivaitve_xx_m(KamadaKawai *kk, int index)
{
    double sum = 0;

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

        double additive = kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * y2) / x2_y2_3_2));

        if (isnan(additive))
            continue;

        sum += additive;
    }

    return sum;
}

double derivaitve_yy_m(KamadaKawai *kk, int index)
{
    double sum = 0;

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

        double additive = kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * x2) / x2_y2_3_2));

        if (isnan(additive))
            continue;

        sum += additive;
    }

    return sum;
}

double derivaitve_xy_m(KamadaKawai *kk, int index)
{
    double sum = 0;

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

        double additive = kk->k_ij[index][i] * ((kk->l_ij[index][i] * dist_x * dist_y) / x2_y2_3_2);

        if (isnan(additive))
            continue;
            
        sum += additive;
    }

    return sum;
}

int get_delta_max_index(KamadaKawai *kk, double *deltas)
{
    int max_index = -1;
    double max = -1;

    for (int i = 0; i < kk->n; i++)
    {
        if (deltas[i] > max)
        {
            max = deltas[i];
            if (max > kk->epsilon)
                max_index = i;
        }
    }

    return max_index;
}

double get_delta_y(double derivaitve_x_m, double derivaitve_y_m, double derivaitve_xx_m, double derivaitve_yy_m, double derivaitve_xy_m)
{
    return (-(derivaitve_xy_m * derivaitve_x_m) + (derivaitve_xx_m * derivaitve_y_m)) / (-(derivaitve_xx_m * derivaitve_yy_m) + (derivaitve_xy_m * derivaitve_xy_m));
}

double get_delta_x(double derivaitve_x_m, double derivaitve_y_m, double derivaitve_xx_m, double derivaitve_yy_m, double derivaitve_xy_m, double delta_y)
{
    return (-(derivaitve_y_m) - (derivaitve_yy_m * delta_y)) / derivaitve_xy_m;
}

double delta_m(double derivaitve_x, double derivaitve_y)
{
    return sqrt((double)pow(derivaitve_x, 2) + (double)pow(derivaitve_y, 2));
}

double get_delta(KamadaKawai *kk, int index)
{
    double derivaitve_x = derivaitve_x_m(kk, index);
    double derivaitve_y = derivaitve_y_m(kk, index);

    return delta_m(derivaitve_x, derivaitve_y);
}

double *get_delatas(KamadaKawai *kk)
{
    double *deltas = (double *)malloc(kk->n * sizeof(double));

    for (int i = 0; i < kk->n; i++)
    {
        deltas[i] = get_delta(kk, i);
    }

    return deltas;
}