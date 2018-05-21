cmake_minimum_required(VERSION 3.8)
project(Surykatki)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp BruteForce.cpp BruteForce.h Crocodile.hpp Point.hpp Graph.hpp Solver.h Solver.cpp Generator.hpp Controller.hpp)
add_executable(Surykatki ${SOURCE_FILES})