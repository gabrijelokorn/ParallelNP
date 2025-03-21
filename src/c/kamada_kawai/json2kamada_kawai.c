#include <stdlib.h>
#include <stdio.h>
#include <json-c/json.h>
#include <stdint.h>
#include <limits.h>

#include "./json2kamada_kawai.h"

int **d_ij_fun(Edge *edges, int n, int m)
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
        d_ij[edges[i].source - 1][edges[i].target - 1] = 1;
        d_ij[edges[i].target - 1][edges[i].source - 1] = 1;
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

Coord *getCoordinates(json_object *coords, int n)
{
    // Allocate memory for the coordinates
    Coord *coordinates = malloc(n * sizeof(Coord));

    // Loop through the coords array
    for (int i = 0; i < n; i++)
    {
        // Get the i-th element of the coords array
        struct json_object *coord = json_object_array_get_idx(coords, i);
        struct json_object *x, *y;

        json_object_object_get_ex(coord, "x", &x);
        json_object_object_get_ex(coord, "y", &y);

        // Get the x and y values of the i-th element of the coords array
        coordinates[i].x = json_object_get_double(x);
        coordinates[i].y = json_object_get_double(y);
    }

    return coordinates;
}

Edge *getEdges(json_object *edges, int m)
{
    // Allocate memory for the edges
    Edge *edgesArray = malloc(m * sizeof(Edge));
    
    // Loop through the edges array
    for (int i = 0; i < m; i++)
    {
        // Get the i-th element of the edges array
        struct json_object *edge = json_object_array_get_idx(edges, i);
        struct json_object *source, *target;
        
        json_object_object_get_ex(edge, "source", &source);
        json_object_object_get_ex(edge, "target", &target);
        
        // Get the source and target values of the i-th element of the edges array
        edgesArray[i].source = json_object_get_int(source);
        edgesArray[i].target = json_object_get_int(target);
    }
    
    return edgesArray;
}

KamadaKawai *json2KamadaKawai(char *buffer)
{
    // Allocate memory for the KamadaKawai struct
    KamadaKawai *kamadaKawai = malloc(sizeof(KamadaKawai));
    // Parse the json object
    json_object *parsed_json = json_tokener_parse(buffer);

    // Get the coords array from the json object
    json_object *coords = json_object_object_get(parsed_json, "coords");
    // Get the length of the coords array
    kamadaKawai->n = json_object_array_length(coords);
    // Get ocordinates of the vertices
    kamadaKawai->coords = getCoordinates(coords, kamadaKawai->n);
    
    // Get the edges array from the json object
    json_object *edges = json_object_object_get(parsed_json, "edges");
    // Get the length of the edges array
    kamadaKawai->m = json_object_array_length(edges);
    // Get edges between the vertices
    kamadaKawai->edges = getEdges(edges, kamadaKawai->m);

    // Get the k constant from the json object
    struct json_object *K;
    // Check if the k value exists
    json_object_object_get_ex(parsed_json, "K", &K);
    // Get the k value
    kamadaKawai->K = json_object_get_double(K);

    // Get the e (epsilon) from the json object
    struct json_object *e;
    // Check if the e value exists
    json_object_object_get_ex(parsed_json, "epsilon", &e);
    // Get the e value
    kamadaKawai->epsilon = json_object_get_double(e);

    // Get the display value from the json object
    struct json_object *display;
    // Check if the display value exists
    json_object_object_get_ex(parsed_json, "display", &display);
    // Get the display value
    kamadaKawai->display = json_object_get_double(display);

    // Calculate the d_ij matrix
    kamadaKawai->d_ij = d_ij_fun(kamadaKawai->edges, kamadaKawai->n, kamadaKawai->m);

    // L_0 - length of a side of a display square area
    double L_0 = kamadaKawai->display;

    // Calculate the L: L = L_0 / max(d_ij)
    int max_d_ij = max_d_ij_fun(kamadaKawai->d_ij, kamadaKawai->n);
    double L = L_0 / max_d_ij;

    // Calculate the l_ij - ideal distances between the vertices
    kamadaKawai->l_ij = l_ij_fun(kamadaKawai->d_ij, kamadaKawai->n, L);

    // Calculate the k_ij - spring constants between the vertices
    kamadaKawai->k_ij = k_ij_fun(kamadaKawai->d_ij, kamadaKawai->n, kamadaKawai->K);

    // Return the KamadaKawai struct
    return kamadaKawai;
}