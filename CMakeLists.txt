cmake_minimum_required(VERSION 3.0.0)
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/)
include_directories(${INCLUDE_PATH})

set(HEADERS ${INCLUDE_PATH}/convolution.hpp 
            ${INCLUDE_PATH}/commons.hpp 
            ${INCLUDE_PATH}/threadsafequeue.hpp
            ${INCLUDE_PATH}/custom_exceptions.hpp
            ${INCLUDE_PATH}/scheduler.hpp
            ${INCLUDE_PATH}/cnn.hpp
            ${INCLUDE_PATH}/pooling.hpp
            ${INCLUDE_PATH}/activations.hpp
            ${INCLUDE_PATH}/preprocessing.hpp
            ${INCLUDE_PATH}/softmax.hpp
            ${INCLUDE_PATH}/layer.hpp
            ${INCLUDE_PATH}/crossentropylayer.hpp
            ${INCLUDE_PATH}/cell.hpp
            ${INCLUDE_PATH}/ffnn.hpp
            ${INCLUDE_PATH}/ffnn_newton.hpp    
            ${INCLUDE_PATH}/ffnn_rsprop.hpp    
            ${INCLUDE_PATH}/inetwork.hpp
            ${INCLUDE_PATH}/ffnnbuilder.hpp            
            )

enable_testing()
add_subdirectory("src")
add_subdirectory("tests")
