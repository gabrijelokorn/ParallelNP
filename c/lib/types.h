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
    double K; // constant k
    double epsilon; // epsilon
    double display; // length of a side of a display square area
} KamadaKawai;

typedef struct Vertices
{
    struct Vertices *next;
    double **coordinates;
} Vertices;

#endif