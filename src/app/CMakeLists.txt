cmake_minimum_required(VERSION 3.16)
project(test_cppflow)

find_library(TENSORFLOW_LIB tensorflow HINT $ENV{HOME}/libtensorflow2/lib)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_cppflow main.cpp)
target_include_directories(test_cppflow PRIVATE /path/to/cppflow/include/ $ENV{HOME}/libtensorflow2/include)
target_link_libraries (test_cppflow "${TENSORFLOW_LIB}")
