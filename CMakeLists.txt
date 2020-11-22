cmake_minimum_required(VERSION 3.9)

# Library locations (Change these to the appropriate path on your machine)
set(INCLUDE_DIR C:/DevelopmentLibraries/include/)
set(LIB_DIR C:/DevelopmentLibraries/lib/x64)

# Create a project for VSynth
project(VSynth)
file(GLOB_RECURSE SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
add_executable(VSynth ${SRCS})
target_include_directories(VSynth PUBLIC include)

# Set include and link directories
target_include_directories(VSynth PUBLIC ${INCLUDE_DIR})
target_link_directories(VSynth PUBLIC ${LIB_DIR})

# Link Libraries for SDL2
target_link_libraries(VSynth PUBLIC SDL2)
target_link_libraries(VSynth PUBLIC SDL2main)