# include "./write.h"

#define FREQENCY 3

void writeString(char *filename, char* str)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "%s )-: File pointer is null\n", "writeString");
        return;
    }
    
    fprintf(fp, "%s", str);
    return;
}

void writeJsonObject(FILE *fp, json_object* jobj) {
    if (fp == NULL) {
        fprintf(stderr, "%s )-: File pointer is null\n", "writeJsonObject");
        return;
    }

    const char* json_string = json_object_to_json_string(jobj);
    fprintf(fp, "%s", json_string);
}

void writeJsonArray(char* filename, bool* result, int n) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "%s )-: File pointer is null\n", "writeJsonArray");
        return;
    }

    json_object *jobj = json_object_new_array();
    for (int i = 0; i < n; i++) {
        json_object *jbool = json_object_new_boolean(result[i]);
        json_object_array_add(jobj, jbool);
    }

    writeJsonObject(fp, jobj);
    fclose(fp);
}

void writeVertices(char *filename, Vertices *vertices, int n)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "%s )-: File pointer is null\n, writeVertices");
        return;
    }

    Vertices *temp = vertices;
    int frames = 0;
    while (temp != NULL)
    {
        frames++;
        temp = temp->next;
    }

    int freq = frames / FREQENCY;
    if (freq == 0)
        freq = 1;

    int count = 0;
    while (vertices != NULL)
    {
        count++;
        if (count % freq != 0 && 
        count != 0 && 
        count != 1 && 
        count != 2 &&
        count != frames)
        {
            vertices = vertices->next;
            continue;
        }
        for (int i = 0; i < n; i++)
        {
            fprintf(fp, "%f,%f\n", vertices->coordinates[i][0], vertices->coordinates[i][1]);
        }
        vertices = vertices->next;
        fprintf(fp, "\n");
    }
}
