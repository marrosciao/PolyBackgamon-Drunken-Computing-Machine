#TODO : tester

## Set the compile option
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wshadow -std=c11")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -O2 -DNDEBUG")
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES *.o)

set(HEADER_DIR "./include")
set(SRC_DIR "./src")

add_subdirectory(${HEADER_DIR})
add_subdirectory(${SRC_DIR})

set(INTERFACE_LIBS ${PROJECT_LIBS} sources)

add_library(interface ${INTERFACE_LIBS})
target_link_libraries(interface ${INTERFACE_LIBS}
