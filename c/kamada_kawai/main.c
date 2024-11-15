#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <json-c/json.h>

#include "../lib/parallelNP.h"
#include "./kamada_kawai.h"

#define NAME "C > Kamada-Kawai"

void KamadaKawaiToString(KamadaKawai *kk)
{
    printf("Kamada-Kawai:\n");
    printf("n: %d\n", kk->n);
    printf("m: %d\n", kk->m);
    printf("k: %f\n", kk->K);
    printf("epsilon: %f\n", kk->epsilon);
    printf("display: %f\n", kk->display);

    printf("edges:\n");
    for (int i = 0; i < kk->m; i++)
    {
        printf("%d: [%d,%d]\n", i, kk->edges[i][0], kk->edges[i][1]);
    }

    printf("coords:\n");
    for (int i = 0; i < kk->n; i++)
    {
        printf("%d: [%f,%f]\n", i, kk->coordinates[i][0], kk->coordinates[i][1]);
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

void print(char *file, Vertices *result, int n)
{
    FILE *fp = fopen(file, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "%s )-: Unable to open file %s\n", NAME, file);
        return;
    }

    writeVertices(fp, result, n);
}

int main(int argc, char *argv[])
{
    bool verbose = false;
    char *test;
    char *outS;
    char *outP;
    bool help = false;

    int opt;
    while ((opt = getopt(argc, argv, ":t:x:y:v")) != -1)
    {
        switch (opt)
        {
        case 't':
            test = optarg;
            break;
        case 'v':
            verbose = true;
            break;
        case 'x':
            outS = optarg;
            break;
        case 'y':
            outP = optarg;
            break;
        case ':':
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
        fprintf(stderr, "%s [-v] -t <test> -x <sequential> -y <parallel>\n", argv[0]);
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

    // A) Sequential
    Vertices *resultS = seq(kamadaKawai);

    // B) Parallel

    // 8) Write the output files
    print(outS, resultS, kamadaKawai->n);

    return 0;
}