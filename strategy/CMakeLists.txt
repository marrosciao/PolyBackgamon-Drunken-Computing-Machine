cmake_minimum_required(VERSION 2.8)
project(strategy)

## Set the compile option
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wshadow -std=c11 -pipe -fdiagnostics-color=auto")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -O2 -DNDEBUG")
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)

set(HEADER_DIR "include")
set(SRC_DIR "src")

set(STRATEGY_VIMPROJECT "Strategy Files=. filter=${HEADER_FILES} ${SRC_FILES}{\n}\n")

set(STRATEGY_SRC_DIR ${SRC_DIR})
set(STRATEGY_HEADER_DIR ${HEADER_DIR})

include_directories(${HEADER_DIR})

add_subdirectory(${HEADER_DIR})
add_subdirectory(${SRC_DIR})

file(GLOB SRC "src/*.c" *.c)
message(${SRC})
add_library(${PROJECT_NAME} SHARED ${SRC})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
