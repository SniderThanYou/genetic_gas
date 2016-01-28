cmake_minimum_required(VERSION 3.4)
project(genetic_gas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp gas_specimen.h gauss_specimen.h population.h)
add_executable(genetic_gas ${SOURCE_FILES})