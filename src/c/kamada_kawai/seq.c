#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./kamada_kawai.h"

float derivaitve_x_m(float **coords, float **l_ij, float **k_ij, int index, int n)
{
    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == index)
            continue;

        float dist_x = coords[index][0] - coords[i][0];
        float dist_y = coords[index][1] - coords[i][1];

        sum += k_ij[index][i] * (dist_x - ((l_ij[index][i] * dist_x) / ((float)pow((float)pow(dist_x, 2) + (float)pow(dist_y, 2), (float)1 / 2))));
    }

    return sum;
}

float derivaitve_y_m(float **coords, float **l_ij, float **k_ij, int index, int n)
{
    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == index)
            continue;

        float dist_x = coords[index][0] - coords[i][0];
        float dist_y = coords[index][1] - coords[i][1];

        sum += k_ij[index][i] * (dist_y - ((l_ij[index][i] * dist_y) / ((float)pow((float)pow(dist_x, 2) + (float)pow(dist_y, 2), (float)1 / 2))));
    }

    return sum;
}

float derivaitve_xx_m(float **coords, float **l_ij, float **k_ij, int index, int n)
{
    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == index)
            continue;

        float dist_x = coords[index][0] - coords[i][0];
        float dist_y = coords[index][1] - coords[i][1];

        sum += k_ij[index][i] * (1 - ((l_ij[index][i] * (float)pow(dist_y, 2)) / ((float)pow((float)pow(dist_x, 2) + (float)pow(dist_y, 2), (float)3 / 2))));
    }

    return sum;
}

float derivaitve_yy_m(float **coords, float **l_ij, float **k_ij, int index, int n)
{
    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == index)
            continue;

        float dist_x = coords[index][0] - coords[i][0];
        float dist_y = coords[index][1] - coords[i][1];

        sum += k_ij[index][i] * (1 - ((l_ij[index][i] * (float)pow(dist_x, 2)) / ((float)pow((float)pow(dist_x, 2) + (float)pow(dist_y, 2), (float)3 / 2))));
    }

    return sum;
}

float derivaitve_xy_m(float **coords, float **l_ij, float **k_ij, int index, int n)
{
    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == index)
            continue;

        float dist_x = coords[index][0] - coords[i][0];
        float dist_y = coords[index][1] - coords[i][1];

        sum += k_ij[index][i] * ((l_ij[index][i] * dist_x * dist_y) / ((float)pow((float)pow(dist_x, 2) + (float)pow(dist_y, 2), (float)3 / 2)));
    }

    return sum;
}

int get_max_delta_m_index(float *deltas, int n, float epsilon)
{
    int max_index = -1;
    float max = -1;

    for (int i = 0; i < n; i++)
    {
        if (deltas[i] > max)
        {
            max = deltas[i];
            if (max > epsilon)
                max_index = i;
        }
    }

    return max_index;
}

float delta_m(float derivaitve_x, float derivaitve_y)
{
    return sqrt((float)pow(derivaitve_x, 2) + (float)pow(derivaitve_y, 2));
}

float calculate_delta(float **coords, float **l_ij, float **k_ij, int index, int n)
{
    float derivaitve_x = derivaitve_x_m(coords, l_ij, k_ij, index, n);
    float derivaitve_y = derivaitve_y_m(coords, l_ij, k_ij, index, n);

    return delta_m(derivaitve_x, derivaitve_y);
}

float *calculate_delatas(float **coords, float **l_ij, float **k_ij, int n)
{
    float *deltas = (float *)malloc(n * sizeof(float));

    for (int i = 0; i < n; i++)
    {
        deltas[i] = calculate_delta(coords, l_ij, k_ij, i, n);
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

void copyCoords(float **coords, float **vertices, int n)
{
    for (int i = 0; i < n; i++)
    {
        vertices[i] = (float *)malloc(2 * sizeof(float));
        vertices[i][0] = coords[i][0];
        vertices[i][1] = coords[i][1];
    }
}

Vertices *seq(KamadaKawai *kk)
{
    Vertices *vertices = (Vertices *)malloc(sizeof(Vertices));
    vertices->coordinates = (float **)malloc(kk->n * sizeof(float *));
    copyCoords(kk->coordinates, vertices->coordinates, kk->n);

    Vertices *vertices_head = vertices;
    
    float epsilon = kk->epsilon;

    float *deltas = calculate_delatas(kk->coordinates, kk->l_ij, kk->k_ij, kk->n);
    // print deltas here
    // for (int i = 0; i < kk->n; i++)
    // {
    //     printf("delta[%d] = %f\n", i, deltas[i]);
    // }
    int max_delta_m_index = get_max_delta_m_index(deltas, kk->n, epsilon);

    while (max_delta_m_index != -1)
    {
        while (deltas[max_delta_m_index] > epsilon)
        {
            float d_x_m = derivaitve_x_m(kk->coordinates, kk->l_ij, kk->k_ij, max_delta_m_index, kk->n);
            float d_y_m = derivaitve_y_m(kk->coordinates, kk->l_ij, kk->k_ij, max_delta_m_index, kk->n);
            float d_xx_m = derivaitve_xx_m(kk->coordinates, kk->l_ij, kk->k_ij, max_delta_m_index, kk->n);
            float d_yy_m = derivaitve_yy_m(kk->coordinates, kk->l_ij, kk->k_ij, max_delta_m_index, kk->n);
            float d_xy_m = derivaitve_xy_m(kk->coordinates, kk->l_ij, kk->k_ij, max_delta_m_index, kk->n);

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

            kk->coordinates[max_delta_m_index][0] += delta_x;
            kk->coordinates[max_delta_m_index][1] += delta_y;

            deltas[max_delta_m_index] = calculate_delta(kk->coordinates, kk->l_ij, kk->k_ij, max_delta_m_index, kk->n);
        }
        vertices->next = (Vertices *)malloc(sizeof(Vertices));
        vertices->next->coordinates = (float **)malloc(kk->n * sizeof(float *));
        copyCoords(kk->coordinates, vertices->next->coordinates, kk->n);

        vertices = vertices->next;

        deltas = calculate_delatas(kk->coordinates, kk->l_ij, kk->k_ij, kk->n);
        max_delta_m_index = get_max_delta_m_index(deltas, kk->n, epsilon);
    }


    return vertices_head;
}