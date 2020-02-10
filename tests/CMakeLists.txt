cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_REQUIRED_FLAGS -std=c++17)

include(CTest)
enable_testing()

find_package(Armadillo  REQUIRED)
find_package (Threads)
find_package( OpenCV REQUIRED )

set(Boost_USE_STATIC_LIBS        OFF)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost REQUIRED COMPONENTS date_time filesystem system regex)
if(!Boost_FOUND)
	message( FATAL_ERROR  "BOOST LIBS not found!!")
endif()

include_directories(${Boost_INCLUDE_DIRS})   
include_directories(/usr/local/include)
include_directories(${ARMADILLO_INCLUDE_DIRS})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


#file(GLOB files "test_*.cc")
set(TEST_FILES  test_queue.cpp 
				test_convolute.cpp 
				test_opencv.cpp
				test_ffnn_newtonraphson.cpp
				test_ffnn_rsprop.cpp
				test_softmax.cpp
				test_series.cpp
				test_frame.cpp
				test_postreg.cpp
				) 

foreach(file ${TEST_FILES})
	string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" file_without_ext ${file})
	add_executable(${file_without_ext} ${file} ${HEADERS})	
	target_link_libraries(${file_without_ext} AIx ${PROJECT_LIBS} ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}  ${Boost_LIBRARIES} ${OpenCV_LIBS})	
	set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++17 ")
	target_include_directories(${file_without_ext} PUBLIC ${INCLUDE_PATH})
	add_test(${file_without_ext} ${file_without_ext})
	set_tests_properties(${file_without_ext}
		PROPERTIES
		PASS_REGULAR_EXPRESSION "OK")
	set_tests_properties(${file_without_ext}
		PROPERTIES
		FAIL_REGULAR_EXPRESSION "(Exception|Test failed)")
	set_tests_properties(${file_without_ext}
		PROPERTIES
		TIMEOUT 120)
endforeach()
