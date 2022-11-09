cmake_minimum_required(VERSION 3.18)
project(smart_ptr)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(unique_ptr unique_ptr.cpp)
add_executable(shared_ptr shared_ptr.cpp)
add_executable(pimpl pimpl.cpp pimpl_main.cpp)