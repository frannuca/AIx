cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

find_package(Armadillo  REQUIRED)
find_package (Threads)

include_directories(${ARMADILLO_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/tests)
set(CTEST_BINARY_DIRECTORY ${PROJECT_BINARY_DIR}/tests)


#file(GLOB files "test_*.cc")
set(TEST_FILES test_queue.cpp)

foreach(file ${TEST_FILES})
	string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" file_without_ext ${file})
	add_executable(${file_without_ext} ${file} ${HEADERS})
	target_link_libraries(${file_without_ext} CNN ${PROJECT_LIBS} ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})	
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
