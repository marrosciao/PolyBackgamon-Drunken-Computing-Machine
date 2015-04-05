#TODO : faire la rêgle install
#TODO : ajouter règle pour l'endroit ou creer l'executable
#TODO : regler PB recherche ressources

# Project Info
cmake_minimum_required(VERSION 2.6)
project(PolyBackgamon)

# Testing
enable_testing()
add_test("${PROJECT_NAME}Run" ${PROJECT_NAME})

# définition des chemins pour l'interface et la stratégie
# set(variable valeur ...)
set(INTERFACE_DIR "${PROJECT_BINARY_DIR}/interface")
set(STRATEGY_DIR "${PROJECT_BINARY_DIR}/strategy")
set(RC_PATH "${INTERFACE_DIR}/rc")
set(LIB_PATH "${PROJECT_BINARY_DIR}")

# Définition des chemins des .h
# permet de faire #include"truc.h" et non #include"../include/truc.h"
include_directories("${INTERFACE_DIR}/include")
include_directories("${STRATEGY_DIR}/include")

message("Project C : Backgamon")
message("Graphic interface :")
message("\tDirectory : ${INTERFACE_DIR}")
message("Strategy :")
message("\tDirectory : ${STRATEGY_DIR}")

# Recherche de la SDL
include(FindPkgConfig)
# PKG_SEARCH_MODULE(variable REQUIRED module)
PKG_SEARCH_MODULE(SDL REQUIRED sdl)
PKG_SEARCH_MODULE(SDLIMAGE REQUIRED SDL_ttf>=1.2.0)
include_directories(${SDL_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIRS})
link_libraries( SDL ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} SDLmain dl )

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
	### Génération de Doxyfile à partir d'un fichier patron
	# Défintion des variables à remplacer dans le patron
	set(CMAKE_SRCS_DIR "${INTERFACE_DIR}/include/ ${INTERFACE_DIR}/src/ ${STRATEGY_DIR}/src/ ${STRATEGY_DIR}/include ")
	set(CMAKE_PROJECT_EXT "*.h *.c")
	set(CMAKE_PROJECT_NAME ${PROJECT_NAME})
	# Remplacement des variables
	#configure_file(fichier_entrée fichier_sorti)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
		${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
	)

	# Ajout de la regle doc pour générer la doc
    #add_custom_target(doc 
        #ALL 
        #${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        #WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        #COMMENT "Generating API documentation with Doxygen" VERBATIM
    #)
endif(DOXYGEN_FOUND)

# Création d'un fichier de config contenant des variables utiles
configure_file(
	"${INTERFACE_DIR}/include/config.h.in"
	"${INTERFACE_DIR}/include/config.h"
)

# Définition du type de compilation et des flags de compilation
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wshadow -std=c11 -pipe -fdiagnostics-color=auto")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -g -fsanitize=address")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -O2 -DNDEBUG")
# Ajout de propriété pour la règle clean
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.so)

### Compilation de l'executable
# On indique à cmake d'ajouter interface/src à la chaine de compilation
# add_subdirectory indique à cmake qu'il faut compiler (par make) le paramêtre
add_subdirectory("${INTERFACE_DIR}/src/")
set(PROJECT_LIBS ${PROJECT_LIBS} sources)
# On indique comment créer l'executable
# add_executable(executable sources ...)
add_executable(${PROJECT_NAME} "${INTERFACE_DIR}/main.c")
# On indique les bibliothèques à lier
#target_link_libraries(executable/bibliothèque bibliothèques ...)
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})

# On indique à cmake de compiler la bibliothèque statique
add_subdirectory(${STRATEGY_DIR})
