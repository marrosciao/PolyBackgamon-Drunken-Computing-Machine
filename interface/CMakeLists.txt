# Info du projet
cmake_minimum_required(VERSION 2.6)
project(Interface)

# Recherche de la SDL
include(FindPkgConfig)
PKG_SEARCH_MODULE(SDL REQUIRED sdl)
PKG_SEARCH_MODULE(SDLIMAGE REQUIRED SDL_ttf>=2.0.0)
include_directories(${SDL_INCLUDE_DIRS})
include_directories(${SDL_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIRS})
link_libraries( SDL ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} SDLmain dl )

## Set the compile options
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wshadow -std=c11 -pipe -fdiagnostics-color=auto -rdynamic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -g -fsanitize=address")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -O2 -DNDEBUG")
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)

# Défintion des chemins, ...
set(HEADER_DIR "include")
set(SRC_DIR "src")
set(INTERFACE_SRC_DIR ${SRC_DIR})
set(INTERFACE_HEADER_DIR ${HEADER_DIR})
set(INTERFACE_LIBS ${PROJECT_LIBS} sources)
set(RC_PATH "${PROJECT_BINARY_DIR}/rc")
set(LIB_PATH "${PROJECT_BINARY_DIR}")

# Création du fichier de config
configure_file(
	"${HEADER_DIR}/config.h.in"
	"${HEADER_DIR}/config.h"
)

# Ajout du répertoire contenant les headers
include_directories(${HEADER_DIR})
include_directories("../strategy/include")

# Ajout de la compilation des sources
add_subdirectory(${SRC_DIR})

# Compilation de l'executable
add_executable(${PROJECT_NAME} "main.c")
target_link_libraries(${PROJECT_NAME} ${INTERFACE_LIBS})
