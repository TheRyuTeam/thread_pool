cmake_minimum_required(VERSION 3.16)
project(pool)

set(CMAKE_CXX_STANDARD 14)

add_executable(pool main.cpp thread_pool.cpp)