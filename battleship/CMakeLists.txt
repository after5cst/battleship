# version 3.15 or later of CMake needed for GoogleTest on Windows
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(battleship)

# set(BUILD_SHARED_LIBS ON)
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS True)

add_library(battleship 
    src/config.cpp
    src/grid.cpp
    src/ship.cpp
    )

# PUBLIC needed to make both battleship.h and battleship library available elsewhere in project
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
#    PRIVATE ${PROJECT_SOURCE_DIR}/extern/cfgpath
    )

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(battleship PUBLIC cxx_std_20)

# add_custom_command(TARGET battleship POST_BUILD 
#   COMMAND "${CMAKE_COMMAND}" -E copy 
#      "$<TARGET_FILE:battleship>"
#      "../apps/$<CONFIGURATION>/$<TARGET_FILE_NAME:battleship>" 
#   COMMENT "Copying to output directory")

#   add_custom_command(TARGET battleship POST_BUILD 
#   COMMAND "${CMAKE_COMMAND}" -E copy 
#      "$<TARGET_FILE:battleship>"
#      "../tests/$<CONFIGURATION>/$<TARGET_FILE_NAME:battleship>" 
#   COMMENT "Copying to tests directory")