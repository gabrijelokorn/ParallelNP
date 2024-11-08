#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <json-c/json.h>

#include "../lib/parallelNP.h"

#define NAME "C > sequential > Kamada-Kawai"

void KamadaKawaiToString(KamadaKawai *kk)
{
    printf("Kamada-Kawai:\n");
    printf("n: %d\n", kk->n);
    printf("m: %d\n", kk->m);
    printf("k: %f\n", kk->k);

    printf("edges:\n");
    for (int i = 0; i < kk->m; i++)
    {
        printf("%d: [%d,%d]\n", i, kk->edges[i][0], kk->edges[i][1]);
    }

    printf("coords:\n");
    for (int i = 0; i < kk->n; i++)
    {
        printf("%d: [%d,%d]\n", i, kk->coordinates[i][0], kk->coordinates[i][1]);
    }
}

void d_ijToString(int **d_ij, int n)
{
    printf("d:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", d_ij[i][j]);
        }
        printf("\n");
    }
}

void l_ijToString(double **l_ij, int n)
{
    printf("l:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ", l_ij[i][j]);
        }
        printf("\n");
    }
}

void k_ijToString(double **k_ij, int n)
{
    printf("k:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ", k_ij[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    bool verbose = false;
    bool sequential = false;
    char *outPointsS;
    char *outPointsP;
    char *outEdgesS;
    char *outEdgesP;
    char *outCoordsS;
    char *outCoordsP;
    char *test;
    bool help = false;

    int opt;
    while ((opt = getopt(argc, argv, ":x:y:z:a:b:c:")) != -1)
    {
        switch (opt)
        {
        case 't':
            test = optarg;
            break;
        case 'v':
            verbose = true;
            break;
        case 's':
            sequential = true;
            break;
        case 'x':
            outPointsS = optarg;
            break;
        case 'y':
            outEdgesS = optarg;
            break;
        case 'z':
            outCoordsS = optarg;
            break;
        case 'a':
            outPointsP = optarg;
            break;
        case 'b':
            outEdgesP = optarg;
            break;
        case 'c':
            outCoordsP = optarg;
            break;
        case ':':
            help = true;
        case '?':
            help = true;
            break;
        }
    }
    if (optind < argc)
        help = true;

    if (help)
    {
        fprintf(stderr, ">->->\n");
        fprintf(stderr, "[WARNING - Unrecognized Arguments] Try:\n");
        fprintf(stderr, "%s [-v] [-s] -p <outPoints> -e <outEdges> -c <outCoords> -o <test>\n", argv[0]);
        fprintf(stderr, "<-<-<\n");
        return 1;
    }

    int n;
    double k;
    int **vertices;
    int **edges;

    // 1) Read the input file
    FILE *inputFile = fopen(test, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "%s )-: Unable to open file %s\n", NAME, argv[1]);
        return 1;
    }
    char *buffer = readFile(inputFile);

    // 2) Parse the input file into json object
    KamadaKawai *kamadaKawai = json2KamadaKawai(buffer);

    // 3) Calculate the d_ij - distances between the vertices - Floyd Warshall
    int **d_ij = d_ij_fun(kamadaKawai->edges, kamadaKawai->n, kamadaKawai->m);

    // 4) Calculate the L_0
    double L_0 = 5;

    // 5) Calculate the L: L = L_0 / max(d_ij)
    int max_d_ij = max_d_ij_fun(d_ij, kamadaKawai->n);
    double L = L_0 / max_d_ij;

    // 6) Calculate the l_ij - ideal distances between the vertices
    double **l_ij = l_ij_fun(d_ij, kamadaKawai->n, L);

    // 7) Calculate the k_ij - spring constants between the vertices
    double **k_ij = k_ij_fun(d_ij, kamadaKawai->n, kamadaKawai->k);

    // KamadaKawaiToString(kamadaKawai);

    return 0;
}