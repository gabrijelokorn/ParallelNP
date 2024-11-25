# include <stdio.h>
# include <json-c/json.h>
# include <stdbool.h>

#include "./write.h"

#define FREQENCY 3

void writeString(FILE *fp, char *str)
{
    fprintf(fp, "%s", str);
    return;
}

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
