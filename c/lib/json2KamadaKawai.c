#include "json2KamadaKawai.h"


// int **getCoordinates(json_array *jsonCoordinates) {
//     int **coordinates = (int **)malloc(jsonCoordinates->length * sizeof(int *));
    
//     return coordinates;

// }

KamadaKawai *json2KamadaKawai(char *buffer)
{
    KamadaKawai *kamadaKawai;

    json_object *jobj = json_tokener_parse(buffer);

    printf("%d\n", sizeof(kamadaKawai));

    int **coordinates;

    return kamadaKawai;
}