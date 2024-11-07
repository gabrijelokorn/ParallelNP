#include "../../lib/parallelNP.h"

#define NAME "C > sequential > Kamada-Kawai"
uint8_t verbose = 0;

void KamadaKawaiToString (KamadaKawai *kk) {
    printf("Kamada-Kawai:\n");
    printf("n: %d\n", kk->n);
    printf("m: %d\n", kk->m);
    printf("k: %f\n", kk->k);

    printf("edges:\n");
    for (int i = 0; i < kk->m; i++) {
        printf("%d: [%d,%d]\n", i, kk->edges[i][0], kk->edges[i][1]);
    }

    printf("coords:\n");
    for (int i = 0; i < kk->n; i++) {
        printf("%d: [%d,%d]\n", i, kk->coordinates[i][0], kk->coordinates[i][1]);
    }
}

void d_ijToString (int **d_ij, int n) {
    printf("d:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", d_ij[i][j]);
        }
        printf("\n");
    }
}

void l_ijToString (double **l_ij, int n) {
    printf("l:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", l_ij[i][j]);
        }
        printf("\n");
    }
}

void k_ijToString (double **k_ij, int n) {
    printf("k:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", k_ij[i][j]);
        }
        printf("\n");
    }
}



int main(int argc, char *argv[])
{
    char *outPoints;
    char *outEdges;
    char *outCoords;
    char *test;

    bool verbose = false;
    bool sequential = false;
    int opt; 
      
    // put ':' in the starting of the 
    // string so that program can  
    //distinguish between '?' and ':'  
    while((opt = getopt(argc, argv, ":p:c:e:o:vs")) != -1)  
    {  
        switch(opt)  
        {  
            case 'v':  
                verbose = true;
                break;
            case 's':  
                sequential = true;
                break;
            case 'p':  
                outPoints = optarg;
                break;  
            case 'e':  
                outEdges = optarg;
                break;  
            case 'c':  
                outCoords = optarg;
                break;  
            case 'o':  
                test = optarg;
                break;  
            case ':':  
                break;  
            case '?':  
                break;  
        }  
    }  
      
    printf("verbose: %d\n", verbose);
    printf("sequential: %d\n", sequential);
    printf("outPoints: %s\n", outPoints);
    printf("outEdges: %s\n", outEdges);
    printf("outCoords: %s\n", outCoords);
    printf("test: %s\n", test);

    // // At least 3 arguments expected:
    // // 1. Program name
    // // 2. Test input file
    // // (3-5). Output file(s) - (number of vertices, coordinates of the vertices, edges between the vertices) / timings
    // // 6. (Optional) Verbose flag

    // for (uint8_t i = 0; i < argc; i++)
    // {
    //     if (strcmp(argv[i], "--verbose") == 0)
    //     {
    //         verbose = 1;
    //     }
    // }

    // int n;
    // double k;
    // int **vertices;
    // int **edges;

    // // 1) Read the input file
    // FILE *inputFile = fopen(argv[1], "r");
    // if (inputFile == NULL)
    // {
    //     fprintf(stderr, "%s )-: Unable to open file %s\n", NAME, argv[1]);
    //     return 1;
    // }

    // char *buffer = readFile(inputFile);

    // // 2) Parse the input file into json object
    // KamadaKawai *kamadaKawai = json2KamadaKawai(buffer);

    // // 3) Calculate the d_ij - distances between the vertices - Floyd Warshall
    // int **d_ij = d_ij_fun(kamadaKawai->edges, kamadaKawai->n, kamadaKawai->m);

    // // 4) Calculate the L_0
    // double L_0 = 5;

    // // 5) Calculate the L: L = L_0 / max(d_ij)
    // int max_d_ij = max_d_ij_fun(d_ij, kamadaKawai->n);
    // double L = L_0 / max_d_ij;

    // // 6) Calculate the l_ij - ideal distances between the vertices
    // double **l_ij = l_ij_fun(d_ij, kamadaKawai->n, L);

    // // 7) Calculate the k_ij - spring constants between the vertices
    // double **k_ij = k_ij_fun(d_ij, kamadaKawai->n, kamadaKawai->k);

    // if (!verbose)
    // {

    // }

    // if (verbose)
    // {
    //     KamadaKawaiToString(kamadaKawai);

    //     // B.1) points.csv - coordinates of the vertices
    //     FILE *outFilePoints = fopen(argv[2], "w");
    //     if (outFilePoints == NULL)
    //     {
    //         fprintf(stderr, "[%s:] Error opening file %s\n", NAME, argv[2]);
    //         return 1;
    //     }
    //     writeString(outFilePoints, "");
    //     writePoints(outFilePoints, kamadaKawai->n);
    //     fclose(outFilePoints);

    //     // B.2) edges.csv - edges between the vertices
    //     FILE *outFileEdges = fopen(argv[4], "w");
    //     if (outFileEdges == NULL)
    //     {
    //         fprintf(stderr, "[%s:] Error opening file %s\n", NAME, argv[2]);
    //         return 1;
    //     }
    //     writeString(outFileEdges, "");
    //     writeEdges(outFileEdges, kamadaKawai->edges, kamadaKawai->m);
    //     fclose(outFileEdges);

    //     d_ijToString(d_ij, kamadaKawai->n);
    //     printf("max_d_ij: %d\n", max_d_ij);
    //     printf("L: %f\n", L);
    //     l_ijToString(l_ij, kamadaKawai->n);
    //     k_ijToString(k_ij, kamadaKawai->n);
        
    // }
    return 0;
}