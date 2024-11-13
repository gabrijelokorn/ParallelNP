#include "json2KamadaKawai.h"

double **getCoordinates (json_object *coords, int n)
{
    // Allocate memory for the coordinates
    double **coordinates = malloc(n * sizeof(double *));
    
    // Loop through the coords array
    for (int i = 0; i < n; i++)
    {
        // Allocate memory for the i-th element of the coordinates
        coordinates[i] = malloc(2 * sizeof(double));

        // Get the i-th element of the coords array
        struct json_object *coord = json_object_array_get_idx(coords, i);
        struct json_object *x, *y;        

        json_object_object_get_ex(coord, "x", &x);
        json_object_object_get_ex(coord, "y", &y);

        // Get the x and y values of the i-th element of the coords array
        coordinates[i][0] = json_object_get_double(x);
        coordinates[i][1] = json_object_get_double(y);   
    }
    
    return coordinates;
}

int **getEdges (json_object *edges, int m)
{
    // Allocate memory for the edges
    int **edgesArray = malloc(m * sizeof(int *));
    
    // Loop through the edges array
    for (int i = 0; i < m; i++)
    {
        // Allocate memory for the i-th element of the edges
        edgesArray[i] = malloc(2 * sizeof(int));

        // Get the i-th element of the edges array
        struct json_object *edge = json_object_array_get_idx(edges, i);
        struct json_object *source, *target;        

        json_object_object_get_ex(edge, "source", &source);
        json_object_object_get_ex(edge, "target", &target);

        // Get the source and target values of the i-th element of the edges array
        edgesArray[i][0] = json_object_get_int(source);
        edgesArray[i][1] = json_object_get_int(target);   
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
    kamadaKawai->coordinates = getCoordinates(coords, kamadaKawai->n);


    // Get the edges array from the json object
    json_object *edges = json_object_object_get(parsed_json, "edges");
    // Get the length of the edges array
    kamadaKawai->m = json_object_array_length(edges);
    // Get edges between the vertices
    kamadaKawai->edges = getEdges(edges, kamadaKawai->m);


    // Get the k constant from the json object
    struct json_object *k;
    // Check if the k value exists
    json_object_object_get_ex(parsed_json, "k", &k);
    // Get the k value
    kamadaKawai->k = json_object_get_double(k);

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

    // Return the KamadaKawai struct
    return kamadaKawai;
}