cmake_minimum_required(VERSION 2.8)
project(muduo)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)
#include_directories(/apps/sylar/include)
#link_directories(/apps/sylar/lib64)

#find_library(YAMLCPP yaml-cpp)
#message("***", ${PROJECT_SOURCE_DIR})

set(LIB_SRC
    muduo/base/Timestamp.cc
    muduo/base/Exception.cc
    muduo/base/CurrentThread.cc
    )

add_library(muduo SHARED ${LIB_SRC})
#add_library(muduo_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (muduo_static PROPERTIES OUTPUT_NAME "muduo")

add_executable(Timestamp_test muduo/base/tests/Timestamp_unittest.cc)
add_dependencies(Timestamp_test muduo)
target_link_libraries(Timestamp_test muduo)

add_executable(Atomic_test muduo/base/tests/Atomic_unittest.cc)
add_dependencies(Atomic_test muduo)
target_link_libraries(Atomic_test muduo)

add_executable(Exception_test muduo/base/tests/Exception_test.cc)
add_dependencies(Exception_test muduo)
target_link_libraries(Exception_test muduo)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)