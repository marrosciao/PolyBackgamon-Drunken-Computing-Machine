cmake_minimum_required(VERSION 2.6)
project(Interface)

include(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

## Set the compile option
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wshadow -std=c11")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -O2 -DNDEBUG")
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)

set(HEADER_DIR "./include")
set(SRC_DIR "./src")

set(INTERFACE_SRC_DIR ${SRC_DIR})
set(INTERFACE_HEADER_DIR ${HEADER_DIR})
set(STRATEGY_VIMPROJECT "Strategy Files=. filter=${HEADER_FILES} ${SRC_FILES}{\n}\n")

add_subdirectory(${HEADER_DIR})
add_subdirectory(${SRC_DIR})

include_directories(${HEADER_DIR})
include_directories(${SDL_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

set(INTERFACE_LIBS ${PROJECT_LIBS} sources)

link_libraries (
	SDL2
   ${SDL_LIBRARY}
   ${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
   SDLmain # Sadly not included in SDL_LIBRARY variable
)

add_executable(${PROJECT_NAME} "main.c")
target_link_libraries(${PROJECT_NAME} ${INTERFACE_LIBS})
