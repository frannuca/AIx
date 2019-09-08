cmake_minimum_required(VERSION 3.0.0)
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/)
include_directories(${INCLUDE_PATH})

set(HEADERS       
            ${INCLUDE_PATH}/concurrency/threadsafequeue.hpp            
            ${INCLUDE_PATH}/concurrency/scheduler.hpp
            
            ${INCLUDE_PATH}/custom_exceptions.hpp

            ${INCLUDE_PATH}/preprocessor/preprocessing.hpp 

            
            ${INCLUDE_PATH}/activations.hpp                        
            ${INCLUDE_PATH}/constants.hpp            
            ${INCLUDE_PATH}/crossentropylayer.hpp
            ${INCLUDE_PATH}/loss.hpp
            ${INCLUDE_PATH}/utils.hpp
            
            ${INCLUDE_PATH}/cnn/pooling.hpp
            ${INCLUDE_PATH}/cnn/convolution.hpp
            ${INCLUDE_PATH}/cnn/cnn.hpp
            

            ${INCLUDE_PATH}/mlp/commons.hpp            
            ${INCLUDE_PATH}/mlp/layer.hpp
            ${INCLUDE_PATH}/mlp/softmax.hpp
            ${INCLUDE_PATH}/mlp/cell.hpp
            ${INCLUDE_PATH}/mlp/ffnn.hpp
            ${INCLUDE_PATH}/mlp/ffnn_newton.hpp    
            ${INCLUDE_PATH}/mlp/ffnn_rsprop.hpp    
            ${INCLUDE_PATH}/mlp/inetwork.hpp
            ${INCLUDE_PATH}/mlp/ffnnbuilder.hpp            
            ${INCLUDE_PATH}/mlp/softmax.hpp            
            
            ${INCLUDE_PATH}/nlp/nlpprocessor.hpp            
            ${INCLUDE_PATH}/rnn/lstm.hpp

            ${INCLUDE_PATH}/data/heterogeneouscontainter.hpp
            ${INCLUDE_PATH}/data/series.hpp
            ${INCLUDE_PATH}/data/frame.hpp            
            )

enable_testing()
add_subdirectory("src")
add_subdirectory("tests")
