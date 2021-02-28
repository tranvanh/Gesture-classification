cmake_minimum_required(VERSION 3.16)
project(app_gestures)

add_library(TENSORFLOW_LIB ./include/libtensorflow2/lib/tensorflow.dll)
set_target_properties(TENSORFLOW_LIB PROPERTIES LINKER_LANGUAGE C)

set(CMAKE_CXX_STANDARD 17)

add_executable(app_gestures main.cpp model/CModelWrapper.cpp model/CModelWrapper.h)
target_include_directories(app_gestures PRIVATE ./include/cppflow/include/ ./include/libtensorflow2/include)
target_link_libraries (app_gestures "${TENSORFLOW_LIB}")
