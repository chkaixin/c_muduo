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
    )

add_library(muduo SHARED ${LIB_SRC})
#add_library(muduo_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (muduo_static PROPERTIES OUTPUT_NAME "muduo")

add_executable(test muduo/base/tests/Timestamp_unittest.cc)
add_dependencies(test muduo)
target_link_libraries(test muduo)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)