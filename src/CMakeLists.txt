cmake_minimum_required(VERSION 3.0.0)
project(CNN VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Armadillo  REQUIRED)
find_package (Threads REQUIRED)

include_directories(${ARMADILLO_INCLUDE_DIRS})

set(SOURCES convolution.cpp  custom_exceptions.cpp  cnn.cpp pooling.cpp ${HEADERS})
add_library(CNN ${SOURCES})
target_link_libraries(CNN ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(CNN PUBLIC ${PROJECT_SOURCE_DIR}/include/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
