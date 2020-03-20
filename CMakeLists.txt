cmake_minimum_required(VERSION 3.10.2)  
set(THIS tv_mock)

project(${THIS})

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -pthread")
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(DO_CLANG_FORMAT clang-format)
set(CLANG_OPT "-i")

add_executable(${THIS} test_MockTvController.cpp)

add_custom_target(start COMMAND ${THIS})
add_custom_target(format COMMAND
    ${DO_CLANG_FORMAT} ${CLANG_OPT}
  ../tv_controller.hpp
  ../TV.hpp
  ../MockTvController.hpp
  ../test_MockTvController.cpp
  )

target_link_libraries(${THIS} ${GTEST_LIBRARIES} gtest_main gmock gtest)
