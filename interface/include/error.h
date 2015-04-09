#ifndef ERROR_INCLUDED
#define ERROR_INCLUDED

#include<stdbool.h>
/**
 * @file error.h
 * @author Vincent BONNEVALLE
 * @brief définie la fonction test
 */

typedef const char* String;
typedef void (*err_func)(String);

/**
 * @def test(bool condition, void (*fun)(const char*))
 * @brief Fait appel à la fonction si la condition passé en paramètre est fausse
 * @param condition si ce paramètre est évalueé à faux, le deuxième paramêtre est appelé
 * @param fun       fonction à appeler si la condition est fausse, la chaine de caractère passée en paramètre est la suivante : cf ci-dessous
 *
 *  "[<fichier>]<fonction> (line <ligne>) : <condition>"
 *
 *  avec: 
 *  
 *      fichier   : le fichier dans lequel test à été appelé
 *  
 *      fonction  : la fonction dans laquelle test à été appelé
 *      
 *      ligne     : ligne à laquelle test à été appelé
 *     
 *      condition : la condition sous forme de chaine de caractère
 *
 *  exemple :
 *  @code
 *  // dans test.c
 *  //...
 *  void fun()
 *  {
 *      void f(const char* s){ printf("%s\n",s); }
 *      test(true, f);// ligne 42
 *      test(false, f);// ligne 43
 *      // affichera :
 *      // [test.c]fun (line 43) : false
 *      //...
 *  }
 *  @endcode
 */
#define test(cond, func)\
    _test(cond, #cond, __FILE__, __func__, __LINE__, func)

void _test(bool condition, String cond_str, String file, String func, int line, err_func erfunc);

#endif
