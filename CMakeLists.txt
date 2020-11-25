cmake_minimum_required(VERSION 3.9)

# Library locations (Change these to the appropriate path on your machine)
set(INCLUDE_DIR C:/DevelopmentLibraries/include/)
set(LIB_DIR C:/DevelopmentLibraries/lib/x64)

set(LIB_TYPE STATIC)

# Create a project for VSynth
project(VSynth_project)

file(GLOB_RECURSE VSYNTH_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
add_library(VSynth ${LIB_TYPE} ${VSYNTH_SRCS})
target_include_directories(VSynth PUBLIC include)

# Set include and link directories
target_include_directories(VSynth PUBLIC ${INCLUDE_DIR})
target_link_directories(VSynth PUBLIC ${LIB_DIR})

# Link Libraries for SDL2
target_link_libraries(VSynth PUBLIC SDL2)
target_link_libraries(VSynth PUBLIC SDL2main)

# Piano Example
file(GLOB_RECURSE PIANO_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} examples/piano/src/*.cpp)
add_executable(Piano ${PIANO_SRCS})
target_link_libraries(Piano VSynth)

target_include_directories(Piano PUBLIC include)