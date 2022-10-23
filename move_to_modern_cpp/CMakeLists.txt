cmake_minimum_required(VERSION 3.18)
project(move_to_modern_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(nullptr_vs_0 nullptr_vs_0.cpp)

add_executable(enum_class_vs_enum enum_class_vs_enum.cpp)

add_executable(using_vs_typedef using_vs_typedef.cpp)

add_executable(delete_vs_undefined delete_vs_undefined.cpp)

add_executable(override override.cpp)

add_executable(constexpr constexpr.cpp)