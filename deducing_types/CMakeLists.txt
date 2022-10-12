cmake_minimum_required(VERSION 3.18)
project(deducing_types)

set(CMAKE_CXX_STANDARD 14)

# Boost
set(Boost_DETAILED_FAILURE_MSG ON)
set(Boost_DEBUG on)
set(BOOST_ROOT /opt/homebrew/Cellar/boost/1.80.0)
set(BOOST_INCLUDEDIR ${BOOST_ROOT})
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib)
find_package(Boost COMPONENTS REQUIRED filesystem program_options)
include_directories(${BOOST_ROOT})

# template type deduce.
add_executable(template_type_deduce template_type_deduce.cpp)
target_link_libraries(template_type_deduce ${Boost_LIBRARIES})

# auto type deduce.
add_executable(auto_type_deduce auto_type_deduce.cpp)
target_link_libraries(auto_type_deduce ${Boost_LIBRARIES})