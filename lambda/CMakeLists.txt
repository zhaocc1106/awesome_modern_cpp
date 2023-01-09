cmake_minimum_required(VERSION 3.18)
project(lambda)

set(CMAKE_CXX_STANDARD 17)

# Boost
set(Boost_DETAILED_FAILURE_MSG ON)
set(Boost_DEBUG on)
set(BOOST_ROOT /opt/homebrew/Cellar/boost/1.80.0)
set(BOOST_INCLUDEDIR ${BOOST_ROOT})
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib)
find_package(Boost COMPONENTS REQUIRED filesystem program_options)
include_directories(${BOOST_ROOT}/include)

add_executable(lambda main.cpp)
link_libraries(lambda ${Boost_LIBRARIES})