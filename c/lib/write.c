# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <json-c/json.h>

# include "./write.h"

void writeJsonObject(FILE *fp, json_object* jobj) {
    if (fp == NULL) {
        fprintf(stderr, ")-: File pointer is null\n");
        return;
    }

    const char* json_string = json_object_to_json_string(jobj);
    fprintf(fp, "%s", json_string);
}

void writeVertices(FILE *fp, Vertices *vertices, int n)
{
    if (fp == NULL)
    {
        fprintf(stderr, ")-: File pointer is null\n");
        return;
    }

    Vertices *temp = vertices;
    int frames = 0;
    while (temp != NULL)
    {
        frames++;
        temp = temp->next;
    }

    int freq = frames / 3;
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

void writeString(FILE *fp, char* str)
{
    fprintf(fp, "%s", str);
    return;
}
