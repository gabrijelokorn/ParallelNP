#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./kamada_kawai.h"

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

int get_max_delta_m_index(KamadaKawai *kk, float *deltas)
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

float delta_m(float derivaitve_x, float derivaitve_y)
{
    return sqrt((float)pow(derivaitve_x, 2) + (float)pow(derivaitve_y, 2));
}

float calculate_delta(KamadaKawai *kk, int index)
{
    float derivaitve_x = derivaitve_x_m(kk, index);
    float derivaitve_y = derivaitve_y_m(kk, index);

    return delta_m(derivaitve_x, derivaitve_y);
}

float *calculate_delatas(KamadaKawai *kk)
{
    float *deltas = (float *)malloc(kk->n * sizeof(float));

    for (int i = 0; i < kk->n; i++)
    {
        deltas[i] = calculate_delta(kk, i);
    }

    return deltas;
}

float calculate_delta_y(float derivaitve_x_m, float derivaitve_y_m, float derivaitve_xx_m, float derivaitve_yy_m, float derivaitve_xy_m)
{
    return (-(derivaitve_xy_m * derivaitve_x_m) + (derivaitve_xx_m * derivaitve_y_m)) / (-(derivaitve_xx_m * derivaitve_yy_m) + (derivaitve_xy_m * derivaitve_xy_m));
}

float calculate_delta_x(float derivaitve_x_m, float derivaitve_y_m, float derivaitve_xx_m, float derivaitve_yy_m, float derivaitve_xy_m, float delta_y)
{
    return (-(derivaitve_y_m) - (derivaitve_yy_m * delta_y)) / derivaitve_xy_m;
}

void copyCoords(Coord *kk_coords, Coord *v_coords, int n)
{
    for (int i = 0; i < n; i++)
    {
        v_coords[i].x = kk_coords[i].x;
        v_coords[i].y = kk_coords[i].y;
    }
}

Vertices *seq(KamadaKawai *kk)
{
    Vertices *vertices = (Vertices *)malloc(sizeof(Vertices));
    vertices->coords = (Coord *)malloc(kk->n * sizeof(Coord *));
    copyCoords(kk->coords, vertices->coords, kk->n);

    Vertices *vertices_head = vertices;

    float *deltas = calculate_delatas(kk);
    int max_delta_m_index = get_max_delta_m_index(kk, deltas);

    while (max_delta_m_index != -1)
    {
        while (deltas[max_delta_m_index] > kk->epsilon)
        {
            float d_x_m = derivaitve_x_m(kk, max_delta_m_index);
            float d_y_m = derivaitve_y_m(kk, max_delta_m_index);
            float d_xx_m = derivaitve_xx_m(kk, max_delta_m_index);
            float d_yy_m = derivaitve_yy_m(kk, max_delta_m_index);
            float d_xy_m = derivaitve_xy_m(kk, max_delta_m_index);

            float delta_y = calculate_delta_y(
                d_x_m,
                d_y_m,
                d_xx_m,
                d_yy_m,
                d_xy_m);

            float delta_x = calculate_delta_x(
                d_x_m,
                d_y_m,
                d_xx_m,
                d_yy_m,
                d_xy_m,
                delta_y);

            kk->coords[max_delta_m_index].x += delta_x;
            kk->coords[max_delta_m_index].y += delta_y;

            deltas[max_delta_m_index] = calculate_delta(kk, max_delta_m_index);
        }
        vertices->next = (Vertices *)malloc(sizeof(Vertices));
        vertices->next->coords = (Coord *)malloc(kk->n * sizeof(Coord *));
        copyCoords(kk->coords, vertices->next->coords, kk->n);
        vertices = vertices->next;

        deltas = calculate_delatas(kk);
        max_delta_m_index = get_max_delta_m_index(kk, deltas);
    }


    return vertices_head;
}