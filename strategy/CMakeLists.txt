# Info du projet
cmake_minimum_required(VERSION 2.8)
project(strategy)

# Set the compile option
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wshadow -std=c11 -pipe -fdiagnostics-color=auto")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -g -fsanitize=address")
#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -O2 -DNDEBUG")
#set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)

# Définition des chemins, ...
set(HEADER_DIR "include")
set(SRC_DIR "src")
set(STRATEGY_SRC_DIR ${SRC_DIR})
set(STRATEGY_HEADER_DIR ${HEADER_DIR})
set(PROJECT_LIBS ${PROJECT_LIBS} sources)

# Définiton du chemin pour les headers
include_directories(${HEADER_DIR})

# Compilation des sources
file(GLOB SRC "src/*.c" *.c)
# add_library(nom_biblio SHARED sources ...) -> construit une bibliothèque dynamique
add_library(${PROJECT_NAME} SHARED ${SRC})
# Il faut indiquer le langage pour le linker si on fait un bibliothèque dynamique
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
