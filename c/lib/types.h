#ifndef TYPES_H
#define TYPES_H

typedef struct dimensions {
    int quantity;
    int rows;
    int *cols;
} dimensions;

typedef struct KamadaKawai {
    int **coordinates;
    int **edges;
    int k;
} KamadaKawai;

#endif