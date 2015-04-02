#TODO : ajouter la regle pour chercher les .h au bon endroit
#TODO : faire la rêgle install
#TODO : ajouter règle pour l'endroit ou creer l'executable
#TODO : regler PB recherche ressources
#TODO : refaire la compilation de tout

# Project Info
cmake_minimum_required(VERSION 2.6)
project(PolyBackgamon)
message("Project C : Backgamon")
message("Graphique interface :")
message("\t Source   directory : ${interface_SOURCE_DIR}")
message("\t Binarie  directory : ${interface_BINARY_DIR}")
message("Strategy :")
message("\t Source   directory : ${strategy_SOURCE_DIR}")
message("\t Binarie  directory : ${strategy_BINARY_DIR}")

# Testing
enable_testing()
add_test("${PROJECT_NAME}Run" ${PROJECT_NAME})

set(INTERFACE_DIR "${PROJECT_BINARY_DIR}/interface")
set(STRATEGY_DIR "${PROJECT_BINARY_DIR}/strategy")

include(FindPkgConfig)
PKG_SEARCH_MODULE(SDL REQUIRED sdl)
PKG_SEARCH_MODULE(SDLIMAGE REQUIRED SDL_image>=2.0.0)

file(WRITE ".vimprojects" "My Project=${PROJECT_BINARY_DIR} CD=. {\n
	CMakeLists.txt\n
	${STRATEGY_VIMPROJECT}\n
	${INTERFACE_VIMPROJECT}\n
	}") #déplacer dans chaque sous-partie ???

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
	set(CMAKE_SRCS_DIR 
		"
		${INTERFACE_DIR}/${INTERFACE_SRC_DIR} 
		${INTERFACE_DIR}/${INTERFACE_HEADER_DIR} 
		${STRATEGY_DIR}/${STRATEGY_SRC_DIR} 
		${STRATEGY_DIR}/${STRATEGY_HEADER_DIR}
		")#laisser un espace après chaque fichier
	set(CMAKE_PROJECT_EXT "*.h *.c")
	set(CMAKE_PROJECT_NAME ${PROJECT_NAME})
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
		${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
		)
	add_custom_target(doc 
		ALL 
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif(DOXYGEN_FOUND)

file(
	COPY
	${STRATEGY_DIR}/${STRATEGY_SRC_DIR}/libstrategy.so
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/
)

## Set the compile option
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wshadow -std=c11 -pipe -fdiagnostics-color=auto")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -O2 -DNDEBUG")
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)

set(PROJECT_LIBS ${PROJECT_LIBS} interface)

include_directories(${SDL_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIRS})

link_libraries (
	SDL
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
	SDLmain # Sadly not included in SDL_LIBRARY variable
	dl
)

add_executable(${PROJECT_NAME} "${INTERFACE_DIR}/main.c")
#target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
