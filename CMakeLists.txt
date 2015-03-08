#TODO : tester pour voir si ça marche

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

## Set the compile option
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wshadow -std=c11")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -O2 -DNDEBUG")
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)

set(PROJECT_LIBS ${PROJECT_LIBS} interface)

add_executable(Backgamon main.c)
target_link_libraries(Backgamon ${PROJECT_LIBS})
