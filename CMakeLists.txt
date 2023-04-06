cmake_minimum_required(VERSION 3.24)
project(Cedar)

set(CMAKE_CXX_STANDARD 23)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(Boost_DETAILED_FAILURE_MSG ON)
set(Boost_DEBUG on)
set(BOOST_ROOT D:/Boost/boost_1.81_0)
set(BOOST_INCLUDE_DIR ${BOOST_ROOT}/boost)
set(BOOST_LIBRARY_DIR ${BOOST_ROOT}/lib)
find_package(Boost COMPONENTS REQUIRED filesystem program_options log)

add_executable(Cedar CedarApplication.cpp)

include_directories(${BOOST_ROOT} ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Cedar ${Boost_LIBRARIES})
