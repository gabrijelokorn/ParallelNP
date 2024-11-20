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
    int n;                // number of vertices
    float **coordinates; // coordinates of the vertices

    int m;       // number of edges
    int **edges; // edges between the vertices

    int **d_ij;
    float **l_ij;
    float **k_ij;

    float K;       // constant k
    float epsilon; // epsilon
    float display; // length of a side of a display square area
} KamadaKawai;

typedef struct Vertices
{
    struct Vertices *next;
    float **coordinates;
} Vertices;

#endif