#ifndef KAMADA_KAWAI_ALGO
#define KAMADA_KAWAI_ALGO

#include <stdio.h>
#include <stdlib.h>

#include "../../common/parallelNP.h"

#include "../json2kamada_kawai.h"
#include "../kamada_kawai2csv.h"

void algo(KamadaKawai *kamadaKawai, char *testcase, bool verbose);
Vertices *seq(KamadaKawai *kamadaKawai);
Vertices *par(KamadaKawai *kamadaKawai);

#endif