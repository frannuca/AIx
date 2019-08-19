#ifndef CONVOLUTION_H
#define CONVOLUTION_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <armadillo>
#include <functional>
#include <memory>
#include "../concurrency/scheduler.hpp"
namespace AIX{
namespace CNN{

using namespace Concurrency;
/**
 * Generates a convolution function on 2D images, represented as matrix.
 * @param imagex is the input images to be convoluted.
 * @param stridex is the stride along the horizontal dimension.
 * @param stridey is the stride along the vertical dimension
 * @param pScheduler is the instance of the thread pool scheduler used to parallelized the convolution operation.
 * @returns a function accepting as parameters the filter to be convoluted and returning the convolution image x filter
 */
std::function<arma::mat(const arma::mat&)> get_convolute(const arma::mat& imagex,size_t stridex, size_t stridey,Scheduler<void>& pScheduler);
    
}
}
#endif