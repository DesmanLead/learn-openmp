cmake_minimum_required(VERSION 2.8.4)
project(mplearn)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES
    main.cpp
    utils.h
    utils.cpp
    pi.h
    pi.cpp
    matrix_sum.h
    matrix_sum.cpp
    simpson.h
    simpson.cpp
    linear.h
    linear.cpp
)
add_executable(mplearn ${SOURCE_FILES})