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

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE INC_FILES ${PROJECT_SOURCE_DIR}/include/*.h)

set(SRC_FILES ${SRC_FILES} ${INC_FILES})
add_definitions(-D_WIN32_WINNT=0x0601)
add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
add_executable(${PROJECT_NAME} CedarApplication.cpp ${SRC_FILES})

foreach (_var ${SRC_FILES})
    message(${_var})
endforeach ()

link_libraries(${Boost_LIBRARIES})

include_directories(${BOOST_ROOT} ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Cedar ${Boost_LIBRARIES})