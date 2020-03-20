cmake_minimum_required(VERSION 3.10.2)  
set(THIS tv_mock)

project(${THIS})

set(CMAKE_CXX_STANDARD 14)            
set(SOURCE_FILES main.cpp)
set(DO_CLANG_FORMAT clang-format)
set(CLANG_OPT "-i")



add_executable(${THIS} ${SOURCE_FILES})

add_custom_target(start COMMAND ${THIS})
add_custom_target(format COMMAND
    ${DO_CLANG_FORMAT} ${CLANG_OPT}
  ../tv_controller.hpp
  ../TV.hpp
  )
