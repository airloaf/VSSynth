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

# Sequenced Beat Example
file(GLOB_RECURSE SEQ_BEAT_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} examples/sequenced_beat/src/*.cpp)
add_executable(SeqBeat ${SEQ_BEAT_SRCS})
target_link_libraries(SeqBeat VSynth)

target_include_directories(SeqBeat PUBLIC include)

# Doxygen Docs
# Look for package, Doxygen
find_package(Doxygen)
# If we have doxygen installed, generate documentation
if(DOXYGEN_FOUND)
    # Set the input and cmake doxygen files
    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYFILE_CMAKE ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile_cmake)

    # Make a copy of the input doxygen file. CMake will generate a custom doxyfile
    configure_file(${DOXYFILE_IN} ${DOXYFILE_CMAKE} @ONLY)

    # Command to generate the documentation
    add_custom_target(documentation 
        ${DOXYGEN_EXECUTABLE} ${DOXYFILE_CMAKE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs)
endif()
