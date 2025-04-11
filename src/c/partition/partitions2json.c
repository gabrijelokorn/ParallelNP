# include <stdio.h>
# include <json-c/json.h>
# include <stdbool.h>
#include "../common/parallelNP.h"

#include "./partitions2json.h"

void writeJsonObject(FILE *fp, json_object *jobj)
{
    if (fp == NULL)
    {
        fprintf(stderr, "%s )-: File pointer is null\n", "writeJsonObject");
        return;
    }

    const char *json_string = json_object_to_json_string(jobj);
    fprintf(fp, "%s", json_string);
}

void writeJsonArray(FILE *fp, bool *result, int n)
{
    json_object *jobj = json_object_new_array();
    for (int i = 0; i < n; i++)
    {
        json_object *jbool = json_object_new_boolean(result[i]);
        json_object_array_add(jobj, jbool);
    }

    writeJsonObject(fp, jobj);
}

void writePartitions(FILE *fp, bool* result, int n) {
    if (fp == NULL)
    {
        fprintf(stderr, "%s )-: File pointer is null\n", "writePartitions");
        return;
    }
    if (result == NULL)
    {
        fprintf(stderr, "%s )-: Result array is null\n", "writePartitions");
        return;
    }
    if (n <= 0)
    {
        fprintf(stderr, "%s )-: Invalid size of result array\n", "writePartitions");
        return;
    }

    writeJsonArray(fp, result, n);
}
