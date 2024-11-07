#ifndef KK
#define KK

#include <stdlib.h>
#include <limits.h>

int **d_ij_fun (int **edges, int n, int m);
double **l_ij_fun (int **d_ij, int n, double L);
double **k_ij_fun (int **d_ij, int n, double k);

int max_d_ij_fun (int **d_ij, int n);

#endif