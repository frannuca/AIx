#ifndef CONVOLUTION_H
#define CONVOLUTION_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <armadillo>
#include <functional>
#include <memory>
#include "scheduler.hpp"
namespace cnn{

using namespace concurrency;
/**
 * Convolutes a 2D images, being a the original image and b the scentil or filter to be applied
 */
std::function<arma::mat(const arma::mat&)> get_convolute(const arma::mat& a,size_t stridex, size_t stridey,std::unique_ptr<Scheduler<double>> pScheduler);
    
}

#endif