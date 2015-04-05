#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "arraylist.h"

const size_t list_min_size = 10;

struct ArrayList {
    TypeContent *array;
    size_t len_content;
    size_t len_array;
};

void list_resize(ArrayList *list);
size_t max(size_t a, size_t b);

ArrayList *list_new() {
    ArrayList *list = calloc(1, sizeof *list);
    assert(list);

    list_resize(list);

    return list;
}

void list_free(ArrayList *list) {
    free(list->array);
    free(list);
}

bool list_get(ArrayList *list, size_t i, TypeContent *item) {
    if (i >= list->len_content) {
        return false;
    }

    *item = list->array[i];
    return true;
}

bool list_set(ArrayList *list, size_t i, TypeContent item) {
    if (i >= list->len_content) {
        return false;
    }

    list->array[i] = item;
    return true;
}

bool list_pop(ArrayList *list, TypeContent *item) {
    if (!list->len_content) {
        return false;
    }

    list->len_content -= 1;
    *item = list->array[list->len_content];
    if (list->len_array >= 3 * list->len_content) {
        list_resize(list);
    }

    return true;
}

bool list_push(ArrayList *list, TypeContent item) {
    if (list->len_content >= list->len_array) {
        list_resize(list);
    }

    list->array[list->len_content] = item;
    list->len_content += 1;

    return true;
}

bool list_splice(ArrayList *list, size_t i, size_t len) {
    // Plusieurs vérifications pour gérer les overflow.
    if ((i + 1)       > list->len_content ||
        len           > list->len_content ||
        (i + 1) + len > list->len_content) {
        return false;
    }

    memmove(list->array + i,
            list->array + i + len,
            (list->len_content - (i + len)) * sizeof (*list->array));
    list->len_content -= len;

    return true;
}

size_t list_size(ArrayList *list) {
    return list->len_content;
}

void list_resize(ArrayList *list) {
    list->len_array = max(2 * list->len_content, list_min_size);
    list->array = realloc(list->array, list->len_array * sizeof (*list->array));
}

size_t max(size_t a, size_t b) {
    return a >= b ? a : b;
}

void list_foreach(ArrayList *list, TypeContent fn(TypeContent)) {
    for (size_t i = 0; i < list->len_content; i++) {
        list->array[i] = fn(list->array[i]);
    }
}
