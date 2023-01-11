cmake_minimum_required(VERSION 3.18)
project(lambda_usage)

set(CMAKE_CXX_STANDARD 14)

# Boost
set(Boost_DETAILED_FAILURE_MSG ON)
set(Boost_DEBUG on)
set(BOOST_ROOT /opt/homebrew/Cellar/boost/1.80.0)
set(BOOST_INCLUDEDIR ${BOOST_ROOT})
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib)
find_package(Boost COMPONENTS REQUIRED filesystem program_options)
include_directories(${BOOST_ROOT}/include)

add_executable(lambda_usage lambda_usage.cpp)
target_link_libraries(lambda_usage ${Boost_LIBRARIES})

add_executable(bind_vs_lambda bind_vs_lambda.cpp)
target_link_libraries(bind_vs_lambda ${Boost_LIBRARIES})