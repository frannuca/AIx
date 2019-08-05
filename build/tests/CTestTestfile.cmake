# CMake generated Testfile for 
# Source directory: /mnt/c/Users/venus/code/cpp/cnn/tests
# Build directory: /mnt/c/Users/venus/code/cpp/cnn/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_queue "test_queue")
set_tests_properties(test_queue PROPERTIES  FAIL_REGULAR_EXPRESSION "(Exception|Test failed)" PASS_REGULAR_EXPRESSION "OK" TIMEOUT "120")
