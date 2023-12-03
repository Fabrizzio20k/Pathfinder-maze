cmake_minimum_required(VERSION 3.24)
project(BEST_PATH_FIDER_FOR_MAZE)


# Dependencies
include(FetchContent)

set(RAYLIB_VERSION 4.5.0)
FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

# Our Project
set(SOURCE_FILES
        main.cpp
        maze.h
        node.h
        variables.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} raylib)
add_definitions(-DASSETS_PATH=\"${CMAKE_SOURCE_DIR}/assets/\")

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()