#include "writeJson.h"

void writeJsonObject(FILE *fp, json_object* jobj) {
    if (fp == NULL) {
        fprintf(stderr, ")-: File pointer is null\n");
        return;
    }

    const char* json_string = json_object_to_json_string(jobj);
    fprintf(fp, "%s", json_string);
}