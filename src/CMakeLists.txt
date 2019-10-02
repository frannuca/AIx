cmake_minimum_required(VERSION 3.0.0)
project(AIx  VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_REQUIRED_FLAGS -std=c++17)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)

find_package(Armadillo  REQUIRED)
find_package (Threads REQUIRED)
find_package( OpenCV REQUIRED )

set(Boost_USE_STATIC_LIBS        OFF)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS date_time filesystem system 
)
if(!Boost_FOUND)
	message( FATAL_ERROR  "BOOST LIBS not found!!")
endif()

include_directories(${Boost_INCLUDE_DIRS})   
include_directories(${CMAKE_SOURCE_DIR}/include/)

include_directories(${ARMADILLO_INCLUDE_DIRS})


set(SOURCES	utils.cpp	 
			convolution.cpp  
			custom_exceptions.cpp  
			cnn.cpp 
			pooling.cpp 
			activations.cpp 
			preprocessing.cpp 
			softmax.cpp
			crossentropylayer.cpp
			layer.cpp
			cell.cpp
			ffnn.cpp
			ffnn_newton.cpp
			ffnnbuilder.cpp	
			ffnn_rsprop.cpp	
			lstm.cpp	
			softmax.cpp
			loss.cpp
			${HEADERS} ../include/data/seriescrawler.hpp)
		add_library(AIx ${SOURCES})
		target_link_libraries(AIx ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${OpenCV_LIBS})
message(INFO ${CMAKE_SOURCE_DIR})
target_include_directories(AIx PUBLIC ${CMAKE_SOURCE_DIR}/include/)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++17 ")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
