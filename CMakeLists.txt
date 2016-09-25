cmake_minimum_required(VERSION 2.8)

project(graphics)

# Flag to compile using c+11.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Bring the headers, such as Student.h into the project
include_directories(../ ../gl2d/external/googletest/googletest/include)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

# Directories to link libraries.
link_directories(../gl2d)

#Generate the static library from the sources
add_executable(graphics ${SOURCES})

# Link static libraries.
target_link_libraries(graphics gl2d)
