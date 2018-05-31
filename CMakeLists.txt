cmake_minimum_required(VERSION 3.8)
project(Surykatki)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp BruteForce.hpp Crocodile.hpp Point.hpp Graph.hpp Solver.h Solver.cpp Generator.hpp Controller.hpp Statistics.hpp Raster.hpp PixelMap.hpp UniqueSet.hpp)
add_executable(Surykatki ${SOURCE_FILES})