cmake_minimum_required(VERSION 3.20.0)
project(SortingAlgorithms VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/ArraySorter/CountingSorter/CountingSorter.cpp
    ${CMAKE_SOURCE_DIR}/src/SortingAlgorithms.cpp
)