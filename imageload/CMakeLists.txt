
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

cmake_policy(VERSION 2.6)

project(imageload)

include(GNUInstallDirs)

# 1. ENV setup

# 1.1 Include/link path

include_directories("/usr/local/include")
include_directories("/usr/local/include")
include_directories("/usr/local/include")
include_directories("/usr/local/include")


include_directories("${CMAKE_INSTALL_INCLUDEDIR}")

#link_directories("${CMAKE_INSTALL_LIBDIR}")

add_definitions("-std=c++11 -fPIC -Wno-deprecated") #-W -Wall




set(IMAGELOAD_BIN_NAME "imageload")

set(IMAGELOAD_SRC_FILES main.cpp)

#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/include")
#include_directories("${CMAKE_INSTALL_INCLUDEDIR}/ipod")

link_directories("/usr/local/lib/")

add_executable(${IMAGELOAD_BIN_NAME} ${IMAGELOAD_SRC_FILES})

target_link_libraries(${IMAGELOAD_BIN_NAME} opencv_core opencv_highgui opencv_features2d opencv_flann opencv_highgui opencv_imgcodecs)



