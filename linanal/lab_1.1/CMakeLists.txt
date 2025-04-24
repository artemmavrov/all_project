cmake_minimum_required(VERSION 3.28)
project(lab_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_1
        best_file.cpp
        lab_1_tests.cpp
)
