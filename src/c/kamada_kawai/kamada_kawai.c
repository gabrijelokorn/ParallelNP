#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "./kamada_kawai.h"

const float EPSILON = 0.000001;

void copyCoords(Coord *kk_coords, Coord *v_coords, int n)
{
    for (int i = 0; i < n; i++)
    {
        v_coords[i].x = kk_coords[i].x;
        v_coords[i].y = kk_coords[i].y;
    }
}

float derivaitve_x_m(KamadaKawai *kk, int index)
{
    float sum = 0;

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

        float additive = kk->k_ij[index][i] * (dist_x - ((kk->l_ij[index][i] * dist_x) / x2_y2_1_2));
        if (isnan(additive))
            continue;

        sum += additive;
    }

    return sum;
}

float derivaitve_y_m(KamadaKawai *kk, int index)
{
    float sum = 0;

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

        float additive = kk->k_ij[index][i] * (dist_y - ((kk->l_ij[index][i] * dist_y) / x2_y2_1_2));

        if (isnan(additive))
            continue;

        sum += additive;
    }

    return sum;
}

float derivaitve_xx_m(KamadaKawai *kk, int index)
{
    float sum = 0;

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

        float additive = kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * y2) / x2_y2_3_2));

        if (isnan(additive))
            continue;

        sum += additive;
    }

    return sum;
}

float derivaitve_yy_m(KamadaKawai *kk, int index)
{
    float sum = 0;

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

        float additive = kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * x2) / x2_y2_3_2));

        if (isnan(additive))
            continue;

        sum += additive;
    }

    return sum;
}

float derivaitve_xy_m(KamadaKawai *kk, int index)
{
    float sum = 0;

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

        float additive = kk->k_ij[index][i] * ((kk->l_ij[index][i] * dist_x * dist_y) / x2_y2_3_2);

        if (isnan(additive))
            continue;
            
        sum += additive;
    }

    return sum;
}

int get_delta_max_index(KamadaKawai *kk, float *deltas)
{
    int max_index = -1;
    float max = -1;

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

float get_delta_y(float derivaitve_x_m, float derivaitve_y_m, float derivaitve_xx_m, float derivaitve_yy_m, float derivaitve_xy_m)
{
    return (-(derivaitve_xy_m * derivaitve_x_m) + (derivaitve_xx_m * derivaitve_y_m)) / (-(derivaitve_xx_m * derivaitve_yy_m) + (derivaitve_xy_m * derivaitve_xy_m));
}

float get_delta_x(float derivaitve_x_m, float derivaitve_y_m, float derivaitve_xx_m, float derivaitve_yy_m, float derivaitve_xy_m, float delta_y)
{
    return (-(derivaitve_y_m) - (derivaitve_yy_m * delta_y)) / derivaitve_xy_m;
}

float delta_m(float derivaitve_x, float derivaitve_y)
{
    return sqrt((float)pow(derivaitve_x, 2) + (float)pow(derivaitve_y, 2));
}

float get_delta(KamadaKawai *kk, int index)
{
    float derivaitve_x = derivaitve_x_m(kk, index);
    float derivaitve_y = derivaitve_y_m(kk, index);

    return delta_m(derivaitve_x, derivaitve_y);
}

float *get_delatas(KamadaKawai *kk)
{
    float *deltas = (float *)malloc(kk->n * sizeof(float));

    for (int i = 0; i < kk->n; i++)
    {
        deltas[i] = get_delta(kk, i);
    }

    return deltas;
}