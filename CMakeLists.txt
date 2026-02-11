cmake_minimum_required(VERSION 3.28)

# set the project name and version
project(flood-puzzle LANGUAGES CXX VERSION 0.3)

set(CMAKE_CXX_STANDARD 23)

# Generate compile_commands.json for IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

# Dependencies
include(FetchContent)

# Fetch raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW 1
)
FetchContent_MakeAvailable(raylib)

add_library(cppray
    images.cpp 
    button.cpp
)
target_link_libraries(cppray PUBLIC raylib)

add_executable(flood flood.cpp game.cpp block_grid.cpp)
add_executable(animate-test animate-test.cpp animate-loop.cpp)

target_link_libraries(flood cppray raylib)
target_link_libraries(animate-test cppray raylib)
