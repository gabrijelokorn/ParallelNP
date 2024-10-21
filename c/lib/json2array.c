#include <json-c/json.h>
#include <stdlib.h>
#include <stdio.h>

#include "json2array.h"

dimensions *dims (char *buffer) {
    dimensions *d = (dimensions *)malloc(sizeof(dimensions));

    d->rows = 0;
    d->quantity = 0;

    struct json_object *parsed_json, *array, *item;
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    parsed_json = json_tokener_parse(buffer);
    it = json_object_iter_begin(parsed_json);
    itEnd = json_object_iter_end(parsed_json);

    int index = 0;

    while (!json_object_iter_equal(&it, &itEnd)) {
        d->rows += 1;
        json_object_iter_next(&it);
    }

    d->cols = (int *)malloc(d->rows * sizeof(int));

    it = json_object_iter_begin(parsed_json);

    while (!json_object_iter_equal(&it, &itEnd)) {
        const char *key = json_object_iter_peek_name(&it);
        array = json_object_iter_peek_value(&it);

        d->cols[index] = json_object_array_length(array);
        d->quantity += d->cols[index];

        json_object_iter_next(&it);
        index++;
    }

    json_object_put(parsed_json);

    return d;
}



int **json2array (char *buffer, dimensions *d) {
    struct json_object *parsed_json, *array, *item;
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    parsed_json = json_tokener_parse(buffer);
    it = json_object_iter_begin(parsed_json);
    itEnd = json_object_iter_end(parsed_json);

    int **arr = (int **)malloc(d->quantity * sizeof(int *));
    uint8_t index = 0;

    while (!json_object_iter_equal(&it, &itEnd)) {
        const char *key = json_object_iter_peek_name(&it);
        array = json_object_iter_peek_value(&it);

        // Allocate memory for the array
        arr[index] = (int *)malloc(json_object_array_length(array) * sizeof(int));

        for (int i = 0; i < json_object_array_length(array); i++) {
            item = json_object_array_get_idx(array, i);
            arr[index][i] = json_object_get_int(item);
        }

        json_object_iter_next(&it);
        index++;
    }

    json_object_put(parsed_json);

    return arr;
}