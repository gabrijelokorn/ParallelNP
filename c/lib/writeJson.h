#ifndef WRITEJSON_H
#define WRITEJSON_H

#include <json-c/json.h>
#include <stdio.h>

void writeJson(FILE *fp, json_object *jobj);

#endif