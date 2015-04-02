cmake_minimum_required(VERSION 2.6)
project(Interface)

include(FindPkgConfig)
PKG_SEARCH_MODULE(SDL REQUIRED sdl)
PKG_SEARCH_MODULE(SDLIMAGE REQUIRED SDL_image>=2.0.0)

## Set the compile option
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wshadow -std=c11 -pipe -fdiagnostics-color=auto -rdynamic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -O2 -DNDEBUG")
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)

set(HEADER_DIR "include")
set(SRC_DIR "src")

set(INTERFACE_SRC_DIR ${SRC_DIR})
set(INTERFACE_HEADER_DIR ${HEADER_DIR})
set(STRATEGY_VIMPROJECT "Strategy Files=. filter=${HEADER_FILES} ${SRC_FILES}{\n}\n")

include_directories(${HEADER_DIR})

add_subdirectory(${HEADER_DIR})
add_subdirectory(${SRC_DIR})

set(INTERFACE_LIBS ${PROJECT_LIBS} sources)

include_directories(${SDL_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIRS})

link_libraries (
	SDL
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
	SDLmain # Sadly not included in SDL_LIBRARY variable
	dl
)

add_executable(${PROJECT_NAME} "main.c")
target_link_libraries(${PROJECT_NAME} ${INTERFACE_LIBS})
