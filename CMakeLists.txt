 # version 3.15 or later of CMake needed for GoogleTest on Windows
# so let's require it now.
cmake_minimum_required(VERSION 3.15)

project(
    VscodeCmakeBattleship
    VERSION 0.1
    DESCRIPTION "Battleship game (learning project)")

add_subdirectory(battleship)   # look in battleship subdirectory for CMakeLists.txt to process
add_subdirectory(apps)    # look in apps subdirectory for CMakeLists.txt to process
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
    add_subdirectory(tests)
endif() #PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME
