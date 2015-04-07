#pragma once

/**
 * @brief Implémentation d'une ArrayList.
 *
 * Le code est inspiré de l'implémentation de [Open Data Structures]
 * (http://opendatastructures.org/ods-cpp/2_1_Fast_Stack_Operations_U.html).
 */

#include <stddef.h>
#include <stdbool.h>

#include "backgammon.h"

typedef struct {
    SMove mouvement[4] ;
    // tableau des mouvements, jusqu'à 4 possibles
    size_t nombre_mouvements ;
    // nombre de mouvements viables dans cette structure ( entre 0 et 4)
} AIListMoves;
/** Type du contenu de la liste. */
typedef AIListMoves TypeContent;

typedef struct ArrayList ArrayList;

/**
 * @brief Alloue une nouvelle liste.
 *
 * @return La nouvelle liste.
 */
ArrayList *list_new();

/**
 * @brief Désalloue une liste.
 *
 * @param list La liste à désallouer.
 */
void list_free(ArrayList *list);

/**
 * @brief Supprime et retourne le dernier élément de la liste.
 *
 * @param list La liste concernée.
 * @param item Un pointeur vers la variable qui contiendra l'élément.
 *
 * @return `true` si tout s'est bien passé.
 */
bool list_pop(ArrayList *list, TypeContent *item);

/**
 * @brief Ajoute un élément à la fin de la liste.
 *
 * @param list La liste concernée.
 * @param item La valeur à ajouter.
 *
 * @return `true` si tout s'est bien passé.
 */
bool list_push(ArrayList *list, TypeContent item);

/**
 * @brief Retourne un élément de la liste.
 *
 * @param list La liste concernée.
 * @param i L'indice de l'élément à retourner.
 * @param item Un pointeur vers la variable qui contiendra l'élément.
 *
 * @return `true` si tout s'est bien passé.
 */
bool list_get(ArrayList *list, size_t i, TypeContent *item);

/**
 * @brief Modifie un élément de la liste.
 *
 * @param list La liste concernée.
 * @param i L'indice de l'élément à retourner.
 * @param item La valeur à modifier.
 *
 * @return `true` si tout s'est bien passé.
 */
bool list_set(ArrayList *list, size_t i, TypeContent item);

/**
 * @brief Supprime une portion de la liste
 *
 * @param list La liste concernée.
 * @param i L'indice du premier élément à supprimer.
 * @param len Le nombre d'éléments à supprimer.
 *
 * @return `true` si tout s'est bien passé.
 */
bool list_splice(ArrayList *list, size_t i, size_t len);

/**
 * @brief Retourne la taille de la liste
 *
 * @param list La liste concernée.
 *
 * @return La taille de la liste.
 */
size_t list_size(ArrayList *list);

/**
 * @brief Applique une fonction sur chaque élément de la liste.
 *
 * @param list La liste concernée.
 * @param fn La liste à appliquer sur chaque élément.
 */
void list_foreach(ArrayList *list, TypeContent fn(TypeContent));
