#ifndef KAMADA_KAWAI_H
#define KAMADA_KAWAI_H

typedef struct Coord
{
    double x;
    double y;
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
    double **l_ij;
    double **k_ij;

    double K;       // constant k
    double epsilon; // epsilon
    double display; // length of a side of a display square area
} KamadaKawai;

typedef struct Vertices
{
    struct Vertices *next;
    Coord *coords;
} Vertices;

Vertices *seq(KamadaKawai *kk);
Vertices *par(KamadaKawai *kk);

void copyCoords(Coord *kk_coords, Coord *v_coords, int n);
int get_delta_max_index(KamadaKawai *kk, double *deltas);

double get_delta_y(double derivaitve_x_m, double derivaitve_y_m, double derivaitve_xx_m, double derivaitve_yy_m, double derivaitve_xy_m);
double get_delta_x(double derivaitve_x_m, double derivaitve_y_m, double derivaitve_xx_m, double derivaitve_yy_m, double derivaitve_xy_m, double delta_y);

double delta_m(double derivaitve_x, double derivaitve_y);
double get_delta(KamadaKawai *kk, int index);
double *get_delatas(KamadaKawai *kk);

double derivaitve_x_m(KamadaKawai *kk, int index);
double derivaitve_y_m(KamadaKawai *kk, int index);
double derivaitve_xx_m(KamadaKawai *kk, int index);
double derivaitve_yy_m(KamadaKawai *kk, int index);
double derivaitve_xy_m(KamadaKawai *kk, int index);

#endif