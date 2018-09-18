cmake_minimum_required(VERSION 3.12)
project(operators)

set(CMAKE_CXX_STANDARD 17)

add_executable(operators main.cpp Value.hpp Bool.hpp Integer.hpp)