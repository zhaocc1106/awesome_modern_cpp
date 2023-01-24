cmake_minimum_required(VERSION 3.18)
project(templates)

set(CMAKE_CXX_STANDARD 17)

# Boost
set(Boost_DETAILED_FAILURE_MSG ON)
set(Boost_DEBUG on)
set(BOOST_ROOT /opt/homebrew/Cellar/boost/1.80.0)
set(BOOST_INCLUDEDIR ${BOOST_ROOT})
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib)
find_package(Boost COMPONENTS REQUIRED filesystem program_options)
include_directories(${BOOST_ROOT})

add_executable(str_literal_template str_literal_template.cc)
target_link_libraries(str_literal_template ${Boost_LIBRARIES})

add_executable(specialization specialization.cc)
target_link_libraries(specialization ${Boost_LIBRARIES})

add_executable(partial_specialization partial_specialization.cc)
target_link_libraries(partial_specialization ${Boost_LIBRARIES})

add_executable(tuple_iter tuple_iter.cc)
target_link_libraries(tuple_iter ${Boost_LIBRARIES})

add_executable(non_type_template non_type_template.cc)
target_link_libraries(non_type_template ${Boost_LIBRARIES})

add_executable(variable_template variable_template.cc)
target_link_libraries(variable_template ${Boost_LIBRARIES})