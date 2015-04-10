#ifndef _LOGGER_INCLUDED
#define _LOGGER_INCLUDED

#include<stdio.h>
#include<stdbool.h>

/**
 * @file logger.h
 * @author Vincent BONNEVALLE
 * @brief défini les fonctions de manipulation d'un logger
 */

#ifndef LOG_LVL
#define LOG_LVL INFO
#endif

#define LOGGER_SIZE 10
/**
 * @def logging(const char* name, const char* message, Level lvl)
 * @brief Fonction affichant un message
 * @param name    nom du logger
 * @param message message à afficher
 * @param lvl     niveau du logger : permet de déterminer si il faut afficher le message
 * @return 0-> il y a eu une erreur dans l'affichage, 1-> aucune erreur
 */
#define logging(name, message, lvl)\
    p_logging(name, __FILE__, __func__, __LINE__, message, lvl)

//! Enum représentant les différents niveaux de log
typedef enum{
    //! Affiche aucun log (ne pas utiliser avec logging)
    NONE    = 0,
    //! Niveau de log correspondant à une erreur
    ERROR   = 1,
    //! Niveau de log correspondant à un avertissement
    WARNING = 2,
    //! Niveau de log correspondant à une information
    INFO    = 3
} Level;

//! Struct contenant les informations nécéssaires au logging
typedef struct{
    //! fichier associé au logger
    FILE* file;
    //! niveau pour lequel on doit afficher les messages
    Level lvl;
    //! nom du logger
    const char* name;
    //! drapeaux servant à savoir si il faut faire un affichage long
    bool simple_print;
} Logger;

//! Fonction d'initialisation du logger
void    init_logger();
//! Fonction retournant un logger
Logger* get_logger(const char*);
//! Fonction définissant le niveau pour lequel afficher du logger
int     set_level(const char*, Level);
//! Fonction associant un fichier à un logger (si le deuxième paramètre est NULL, on affiche sur stderr)
int     set_file(const char*, const char*);
//! Fonction indiquant si il faut faire un affichage long ou court
void    set_simple_print(const char*, bool);
int     p_logging(const char*, const char*, const char*, const int, const char*, Level);
//! Fonction de libération des loggers
void    free_logger();

#endif
