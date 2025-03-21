#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./kamada_kawai.h"

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

        sum += kk->k_ij[index][i] * (dist_x - ((kk->l_ij[index][i] * dist_x) / ((float)pow((float)pow(dist_x, 2) + (float)pow(dist_y, 2), (float)1 / 2))));
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

        sum += kk->k_ij[index][i] * (dist_y - ((kk->l_ij[index][i] * dist_y) / ((float)pow((float)pow(dist_x, 2) + (float)pow(dist_y, 2), (float)1 / 2))));
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

        sum += kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * (float)pow(dist_y, 2)) / ((float)pow((float)pow(dist_x, 2) + (float)pow(dist_y, 2), (float)3 / 2))));
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

        sum += kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * (float)pow(dist_x, 2)) / ((float)pow((float)pow(dist_x, 2) + (float)pow(dist_y, 2), (float)3 / 2))));
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

        sum += kk->k_ij[index][i] * ((kk->l_ij[index][i] * dist_x * dist_y) / ((float)pow((float)pow(dist_x, 2) + (float)pow(dist_y, 2), (float)3 / 2)));
    }

    return sum;
}

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

// void derivatives_par(KamadaKawai *kk, int index, float *x, float *y, float *xx, float *yy, float *xy)
// {
//     float temp_x, temp_y, temp_xx, temp_yy, temp_xy = 0;
// #pragma omp parallel for schedule(static) reduction(+ : temp_x, temp_y, temp_xx, temp_yy, temp_xy)
//     for (int i = 0; i < kk->n; i++)
//     {
//         if (i == index)
//             continue;

//         float dist_x = kk->coords[index].x - kk->coords[i].x;
//         float dist_y = kk->coords[index].y - kk->coords[i].y;
//         float x2 = (float)pow(dist_x, 2);
//         float y2 = (float)pow(dist_y, 2);
//         float x2_y2 = x2 + y2;
//         float x2_y2_1_2 = (float)sqrt(x2_y2);
//         float x2_y2_3_2 = (float)pow(x2_y2, (float)3 / 2);

//         temp_x += kk->k_ij[index][i] * (dist_x - ((kk->l_ij[index][i] * dist_x) / x2_y2_1_2));
//         temp_y += kk->k_ij[index][i] * (dist_y - ((kk->l_ij[index][i] * dist_y) / x2_y2_1_2));
//         temp_xx += kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * y2) / x2_y2_3_2));
//         temp_yy += kk->k_ij[index][i] * (1 - ((kk->l_ij[index][i] * x2) / x2_y2_3_2));
//         temp_xy += kk->k_ij[index][i] * ((kk->l_ij[index][i] * dist_x * dist_y) / x2_y2_3_2);
//     }
//     *x = temp_x;
//     *y = temp_y;
//     *xx = temp_xx;
//     *yy = temp_yy;
//     *xy = temp_xy;
// }