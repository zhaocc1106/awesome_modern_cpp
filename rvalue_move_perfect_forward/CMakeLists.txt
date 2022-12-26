cmake_minimum_required(VERSION 3.18)
project(rvalue_move_perfect_forward)

set(CMAKE_CXX_STANDARD 17)

# Boost
set(Boost_DETAILED_FAILURE_MSG ON)
set(Boost_DEBUG on)
set(BOOST_ROOT /opt/homebrew/Cellar/boost/1.80.0)
set(BOOST_INCLUDEDIR ${BOOST_ROOT})
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib)
find_package(Boost COMPONENTS REQUIRED filesystem program_options)
include_directories(${BOOST_ROOT})

add_executable(distinguish_rvalue_ref_and_universal_ref distinguish_rvalue_ref_and_universal_ref.cpp)
target_link_libraries(distinguish_rvalue_ref_and_universal_ref ${Boost_LIBRARIES})

add_executable(perfect_forward perfect_forward.cpp)
target_link_libraries(perfect_forward ${Boost_LIBRARIES})
