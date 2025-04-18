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
    int n;         // number of vertices
    Coord *coords; // coordinates of the vertices

    int m;       // number of edges
    Edge *edges; // edges between the vertices

    int **d_ij;
    double **l_ij;
    double **k_ij;

    double **addendx;
    double *dx;
    double **addendy;
    double *dy;

    double *deltas;

    double K;       // constant k
    double epsilon; // epsilon
    double display; // length of a side of a display square area
    double limit;
} KamadaKawai;

void copyCoords(Coord *kk_coords, Coord *v_coords, int n);

double get_delta_m_y(double derivaitve_x_m, double derivaitve_y_m, double derivaitve_xx_m, double derivaitve_yy_m, double derivaitve_xy_m);
double get_delta_m_x(double derivaitve_x_m, double derivaitve_y_m, double derivaitve_xx_m, double derivaitve_yy_m, double derivaitve_xy_m, double delta_y);

double get_delta_m(KamadaKawai *kk, int index);
double update_delta_m(KamadaKawai *kk, int m, int index);
void get_derivatives_seq(KamadaKawai *kk, int index, double *d_m_x, double *d_m_y, double *d_m_xx, double *d_m_yy, double *d_m_xy);
void get_derivatives_par(KamadaKawai *kk, int index, double *d_m_x, double *d_m_y, double *d_m_xx, double *d_m_yy, double *d_m_xy);
int get_deltas_seq(KamadaKawai *kk);
int update_deltas_seq(KamadaKawai *kk, int m);
int get_deltas_par(KamadaKawai *kk);
int update_deltas_par(KamadaKawai *kk, int m);

double get_derivative_x(KamadaKawai *kk, int index);
double get_derivative_y(KamadaKawai *kk, int index);

#endif