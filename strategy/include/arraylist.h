#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "backgammon.h"

typedef struct ArrayList ArrayList;
typedef struct {
    SMove mouvement[4] ;
    // tableau des mouvements, jusqu'à 4 possibles
    size_t nombre_mouvements ;
    // nombre de mouvements viables dans cette structure ( entre 0 et 4)
} AIListMoves;
typedef AIListMoves TypeContent;

ArrayList *list_new();
void list_free(ArrayList *list);

bool list_pop(ArrayList *list, TypeContent *item);
bool list_push(ArrayList *list, TypeContent item);
bool list_get(ArrayList *list, size_t i, TypeContent *item);
bool list_set(ArrayList *list, size_t i, TypeContent item);
bool list_splice(ArrayList *list, size_t i, size_t len);
size_t list_size(ArrayList *list);

void list_foreach(ArrayList *list, TypeContent fn(TypeContent));
