#include <math.h>
#include "./kamada-kawai.h"

double derivaitve_x_m(double **coords, double **l_ij, double **k_ij, int index, int n)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == index)
            continue;

        double dist_x = coords[index][0] - coords[i][0];
        double dist_y = coords[index][1] - coords[i][1];

        sum += k_ij[index][i] * (dist_x - ((l_ij[index][i] * dist_x) / (sqrt((double)pow(dist_x, 2) + (double)pow(dist_y, 2)))));
    }

    return sum;
}

double derivaitve_y_m(double **coords, double **l_ij, double **k_ij, int index, int n)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == index)
            continue;

        double dist_x = coords[index][0] - coords[i][0];
        double dist_y = coords[index][1] - coords[i][1];

        sum += k_ij[index][i] * (dist_y - ((l_ij[index][i] * dist_y) / (sqrt((double)pow(dist_x, 2) + (double)pow(dist_y, 2)))));
    }

    return sum;
}

double derivaitve_xx_m(double **coords, double **l_ij, double **k_ij, int index, int n)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == index)
            continue;

        double dist_x = coords[index][0] - coords[i][0];
        double dist_y = coords[index][1] - coords[i][1];

        sum += k_ij[index][i] * (1 - ((l_ij[index][i] * (double)pow(dist_y, 2)) / ((double)pow((double)pow(dist_x, 2) + (double)pow(dist_y, 2), 3 / 2))));
    }

    return sum;
}

double derivaitve_yy_m(double **coords, double **l_ij, double **k_ij, int index, int n)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == index)
            continue;

        double dist_x = coords[index][0] - coords[i][0];
        double dist_y = coords[index][1] - coords[i][1];

        sum += k_ij[index][i] * (1 - ((l_ij[index][i] * (double)pow(dist_x, 2)) / ((double)pow((double)pow(dist_x, 2) + (double)pow(dist_y, 2), 3 / 2))));
    }

    return sum;
}

double derivaitve_xy_m(double **coords, double **l_ij, double **k_ij, int index, int n)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == index)
            continue;

        double dist_x = coords[index][0] - coords[i][0];
        double dist_y = coords[index][1] - coords[i][1];

        sum += k_ij[index][i] * ((l_ij[index][i] * dist_x * dist_y) / ((double)pow((double)pow(dist_x, 2) + (double)pow(dist_y, 2), 3 / 2)));
    }

    return sum;
}

int get_max_delta_m_index(double *deltas, int n, double epsilon)
{
    int max_index = -1;
    double max = -1;

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

double delta_m(double derivaitve_x, double derivaitve_y)
{
    return sqrt((double)pow(derivaitve_x, 2) + (double)pow(derivaitve_y, 2));
}

double calculate_delta(double **coords, double **l_ij, double **k_ij, int index, int n)
{
    double derivaitve_x = derivaitve_x_m(coords, l_ij, k_ij, index, n);
    double derivaitve_y = derivaitve_y_m(coords, l_ij, k_ij, index, n);

    return delta_m(derivaitve_x, derivaitve_y);
}

double *calculate_delatas(double **coords, double **l_ij, double **k_ij, int n)
{
    double *deltas = (double *)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        deltas[i] = calculate_delta(coords, l_ij, k_ij, i, n);
    }

    return deltas;
}

double calculate_delta_y(double derivaitve_x_m, double derivaitve_y_m, double derivaitve_xx_m, double derivaitve_yy_m, double derivaitve_xy_m)
{
    return (-(derivaitve_xy_m * derivaitve_x_m) + (derivaitve_xx_m * derivaitve_y_m)) / (-(derivaitve_xx_m * derivaitve_yy_m) + (derivaitve_xy_m * derivaitve_xy_m));
}

double calculate_delta_x(double derivaitve_x_m, double derivaitve_y_m, double derivaitve_xx_m, double derivaitve_yy_m, double derivaitve_xy_m, double delta_y)
{
    return (-(derivaitve_y_m) - (derivaitve_yy_m * delta_y)) / derivaitve_xy_m;
}

Vertices *seq(KamadaKawai *kk, int **d_ij, double **l_ij, double **k_ij)
{
    Vertices *vertices = NULL;

    double epsilon = 1.00;

    double *deltas = calculate_delatas(kk->coordinates, l_ij, k_ij, kk->n);

    for (int i = 0; i < kk->n; i++)
    {
        printf("delta[%d] = %f\n", i, deltas[i]);
    }

    int max_delta_m_index = get_max_delta_m_index(deltas, kk->n, epsilon);

    int allowed_iterations = 1000;

    while (max_delta_m_index != -1)
    {
        printf("### --- ### index: %d, val: %f\n", max_delta_m_index, deltas[max_delta_m_index]);
        while (deltas[max_delta_m_index] > epsilon)
        {
            allowed_iterations--;
            double d_x_m = derivaitve_x_m(kk->coordinates, l_ij, k_ij, max_delta_m_index, kk->n);
            double d_y_m = derivaitve_y_m(kk->coordinates, l_ij, k_ij, max_delta_m_index, kk->n);
            double d_xx_m = derivaitve_xx_m(kk->coordinates, l_ij, k_ij, max_delta_m_index, kk->n);
            double d_yy_m = derivaitve_yy_m(kk->coordinates, l_ij, k_ij, max_delta_m_index, kk->n);
            double d_xy_m = derivaitve_xy_m(kk->coordinates, l_ij, k_ij, max_delta_m_index, kk->n);

            double delta_y = calculate_delta_y(
                d_x_m,
                d_y_m,
                d_xx_m,
                d_yy_m,
                d_xy_m);

            double delta_x = calculate_delta_x(
                d_x_m,
                d_y_m,
                d_xx_m,
                d_yy_m,
                d_xy_m,
                delta_y);

            printf("delta_x = %f\n", delta_x);
            printf("delta_y = %f\n", delta_y);

            kk->coordinates[max_delta_m_index][0] += delta_x;
            kk->coordinates[max_delta_m_index][1] += delta_y;

            deltas[max_delta_m_index] = calculate_delta(kk->coordinates, l_ij, k_ij, max_delta_m_index, kk->n);
            if (deltas[max_delta_m_index] < epsilon)
                max_delta_m_index = -1;
            if (allowed_iterations == 0)
                break;
        }
        if (allowed_iterations == 0)
            break;
        max_delta_m_index = get_max_delta_m_index(deltas, kk->n, epsilon);
    }

    for (int i = 0; i < kk->n; i++)
    {
        printf("delta[%d] = %f\n", i, deltas[i]);
    }

    return vertices;
}