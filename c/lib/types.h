#ifndef TYPES_H
#define TYPES_H

typedef struct dimensions
{
    int quantity;
    int rows;
    int *cols;
} dimensions;

typedef struct KamadaKawai
{
    int n; // number of vertices
    double **coordinates; // coordinates of the vertices
    int m; // number of edges
    int **edges; // edges between the vertices
    double k; // constant k
} KamadaKawai;

typedef struct Vertices
{
    struct Vertices *next;
    double **coordinates;
} Vertices;

#endif