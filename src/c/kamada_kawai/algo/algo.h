#ifndef KAMADA_KAWAI_ALGO
#define KAMADA_KAWAI_ALGO

#include <stdio.h>
#include <stdlib.h>

#include "../../common/parallelNP.h"

#include "../json2kamada_kawai.h"
#include "../kamada_kawai2csv.h"

void algo(KamadaKawai *kk, char *num, char *repetitions);

void mem_seq(KamadaKawai *kamadaKawai);
void mem_par(KamadaKawai *kamadaKawai);
void par(KamadaKawai *kamadaKawai);
void mlt_seq(KamadaKawai *kamadaKawai);
void mlt_par(KamadaKawai *kamadaKawai);

#endif