# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.
cmake_minimum_required(VERSION 3.10)
project(WI25-Assignment1)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(WI25-Assignment1 main.cpp MemoryTracker.hpp Sequence.hpp)

# Set compiler warnings
if(MSVC)
    target_compile_options(WI25-Assignment1 PRIVATE /W4)
else()
    target_compile_options(WI25-Assignment1 PRIVATE -Wall -Wextra -Wpedantic)
endif()



