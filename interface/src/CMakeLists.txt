# Recherche de tout les .c
file(GLOB SRC . *.c)
# Compilation en bibliothèque statique
add_library(sources ${SRC})
