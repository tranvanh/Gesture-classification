cmake_minimum_required(VERSION 3.16)
project(app_gestures)

find_library(TENSORFLOW_LIB tensorflow HINT $ENV{HOME}/libtensorflow2/lib)

set(CMAKE_CXX_STANDARD 17)

add_executable(app_gestures main.cpp)
target_include_directories(app_gestures PRIVATE /path/to/cppflow/include/ $ENV{HOME}/libtensorflow2/include)
target_link_libraries (app_gestures "${TENSORFLOW_LIB}")
