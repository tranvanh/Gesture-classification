# Install script for directory: C:/Users/tranv/source/repos/tranvanh/Gesture-classification/src/GestureApp/includes/tensorflow2/tensorflow/lite/out/build/x64-Debug (default)/xnnpack

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/tranv/source/repos/tranvanh/Gesture-classification/src/GestureApp/includes/tensorflow2/tensorflow/lite/out/install/x64-Debug (default)")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tranv/source/repos/tranvanh/Gesture-classification/src/GestureApp/includes/tensorflow2/tensorflow/lite/out/build/x64-Debug (default)/_deps/xnnpack-build/XNNPACK.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/tranv/source/repos/tranvanh/Gesture-classification/src/GestureApp/includes/tensorflow2/tensorflow/lite/out/build/x64-Debug (default)/xnnpack/include/xnnpack.h")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/tranv/source/repos/tranvanh/Gesture-classification/src/GestureApp/includes/tensorflow2/tensorflow/lite/out/build/x64-Debug (default)/clog/cmake_install.cmake")
  include("C:/Users/tranv/source/repos/tranvanh/Gesture-classification/src/GestureApp/includes/tensorflow2/tensorflow/lite/out/build/x64-Debug (default)/cpuinfo/cmake_install.cmake")
  include("C:/Users/tranv/source/repos/tranvanh/Gesture-classification/src/GestureApp/includes/tensorflow2/tensorflow/lite/out/build/x64-Debug (default)/pthreadpool/cmake_install.cmake")
  include("C:/Users/tranv/source/repos/tranvanh/Gesture-classification/src/GestureApp/includes/tensorflow2/tensorflow/lite/out/build/x64-Debug (default)/psimd/cmake_install.cmake")
  include("C:/Users/tranv/source/repos/tranvanh/Gesture-classification/src/GestureApp/includes/tensorflow2/tensorflow/lite/out/build/x64-Debug (default)/FP16/cmake_install.cmake")

endif()
