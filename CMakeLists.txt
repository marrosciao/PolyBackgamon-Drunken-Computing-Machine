#TODO : tester pour voir si ça marche
#TODO : ajouter la regle pour chercher les .h au bon endroit

# Project Info
cmake_minimum_required(VERSION 2.6)
project(Backgamon)
message("Project C : Backgamon")
message("Graphique interface :")
message("\t Source   directory : ${interface_SOURCE_DIR}")
message("\t Binarie  directory : ${interface_BINARY_DIR}")
message("Strategy :")
message("\t Source   directory : ${strategy_SOURCE_DIR}")
message("\t Binarie  directory : ${strategy_BINARY_DIR}")

# Testing
enable_testing()
add_test(BackgamonRun Backgamon)

set(INTERFACE_DIR "${PROJECT_BINARY_DIR}/interface")
set(STRATEGY_DIR "${PROJECT_BINARY_DIR}/strategy")

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
#target_link_libraries(sdl2test ${SDL2_LIBRARIES}) # utilité ?????

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
	set(CMAKE_PROJECT_NAME ${PORJECT_NAME})
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


## Set the compile option
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wshadow -std=c11")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -O2 -DNDEBUG")
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)

set(PROJECT_LIBS ${PROJECT_LIBS} interface)

add_executable(Backgamon main.c)
target_link_libraries(Backgamon ${PROJECT_LIBS})
