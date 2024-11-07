#include "KK.h"

int **d_ij_fun(int **edges, int n, int m)
{
    int **d_ij = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        d_ij[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                d_ij[i][j] = 0;
            else
                d_ij[i][j] = n + 1;
        }
    }

    for (int i = 0; i < m; i++)
    {
        d_ij[edges[i][0] - 1][edges[i][1] - 1] = 1;
        d_ij[edges[i][1] - 1][edges[i][0] - 1] = 1;
    }

    // Do the floyd warshall algorithm
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (d_ij[i][j] > d_ij[i][k] + d_ij[k][j])
                {
                    d_ij[i][j] = d_ij[i][k] + d_ij[k][j];
                }
            }
        }
    }

    return d_ij;
}

double **l_ij_fun(int **d_ij, int n, double L)
{

    double **l_ij = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        l_ij[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++)
        {
            if (i != j)
                l_ij[i][j] = d_ij[i][j] * L;
        }
    }

    return l_ij;
}

double **k_ij_fun(int **d_ij, int n, double k)
{
    double **k_ij = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        k_ij[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++)
        {
            if (i != j)
                k_ij[i][j] = k / (d_ij[i][j] * d_ij[i][j]);
        }
    }

    return k_ij;
}

int max_d_ij_fun(int **d_ij, int n)
{
    int max = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (d_ij[i][j] > max)
            {
                max = d_ij[i][j];
            }
        }
    }

    return max;
}