#ifndef POOLING_H
#define POOLING_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <armadillo>
#include <functional>
#include <memory>
#include "concurrency/scheduler.hpp"
namespace cnn{

using namespace concurrency;
/**
 * Generates a convolution function on 2D images, represented as matrix.
 * @param imagex is the input images to be convoluted.
 * @param stridex is the stride along the horizontal dimension.
 * @param stridey is the stride along the vertical dimension
 * @param pScheduler is the instance of the thread pool scheduler used to parallelized the convolution operation.
 * @returns a function accepting as parameters the filter to be convoluted and returning the convolution image x filter
 */
std::function<arma::mat(int,int)> get_pooling(const arma::mat& imagex,std::shared_ptr<Scheduler<void>> pScheduler);
    
}

#endif