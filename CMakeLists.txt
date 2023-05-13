cmake_minimum_required(VERSION 3.10)
project(array_test)

# Add the includes directory to the include path
include_directories(includes)

# Build the array test executable
add_executable(array
    test/array.cc
    includes/array.hpp
)

# Set the C++ standard to C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")