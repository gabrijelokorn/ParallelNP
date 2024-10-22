#ifndef WRITEJSON_H
#define WRITEJSON_H

#include <json-c/json.h>
#include <stdio.h>

void writeJsonObject(FILE *fp, json_object *jobj);
void writeJsonArray(FILE *fp, json_object *jobj);

#endif