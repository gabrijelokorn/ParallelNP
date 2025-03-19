#ifndef KAMADA_KAWAI_H
#define KAMADA_KAWAI_H

typedef struct Coord
{
    float x;
    float y;
} Coord;

typedef struct Edge
{
    int source;
    int target;
} Edge;

typedef struct KamadaKawai
{
    int n;               // number of vertices
    Coord *coords; // coordinates of the vertices

    int m;       // number of edges
    Edge *edges; // edges between the vertices

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
    Coord *coords;
} Vertices;

Vertices *seq(KamadaKawai *kk);
Vertices *par(KamadaKawai *kk);

void copyCoords(Coord *kk_coords, Coord *v_coords, int n);
float derivaitve_x_m(KamadaKawai *kk, int index);
float derivaitve_y_m(KamadaKawai *kk, int index);
float derivaitve_xx_m(KamadaKawai *kk, int index);
float derivaitve_yy_m(KamadaKawai *kk, int index);
float derivaitve_xy_m(KamadaKawai *kk, int index);

#endif