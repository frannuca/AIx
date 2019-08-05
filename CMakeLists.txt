cmake_minimum_required(VERSION 3.0.0)
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/)
include_directories(${INCLUDE_PATH})

set(HEADERS ${INCLUDE_PATH}/convolution.hpp 
            ${INCLUDE_PATH}/commons.hpp 
            ${INCLUDE_PATH}/threadsafequeue.hpp
            ${INCLUDE_PATH}/custom_exceptions.hpp
            ${INCLUDE_PATH}/scheduler.hpp
            )

add_subdirectory("src")
add_subdirectory("tests")
