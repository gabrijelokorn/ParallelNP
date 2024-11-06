#include "KK.h"

int **d_ij(int **edges, int n, int m) {
    int **d = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        d[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            if (i == j) d[i][j] = 0;
            else d[i][j] = n + 1;
        }
    }

    for (int i = 0; i < m; i++) {
        d[edges[i][0] - 1][edges[i][1] - 1] = 1;
        d[edges[i][1] - 1][edges[i][0] - 1] = 1;
    }

    // Do the floyd warshall algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }

    return d;
}