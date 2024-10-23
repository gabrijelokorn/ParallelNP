#ifndef JSON2KAMADAKAWAI_H
#define JSON2KAMADAKAWAI_H

#include <stdlib.h>
#include <stdio.h>
#include <json-c/json.h>

#include "./types.h"

KamadaKawai *json2KamadaKawai (char* buffer);

#endif