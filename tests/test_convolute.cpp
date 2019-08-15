
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <chrono>
#include <armadillo>
#include "cnn/convolution.hpp"
#include "constants.hpp"
#include "concurrency/threadsafequeue.hpp"
#include "concurrency/scheduler.hpp"

int main(int, char**){
    arma::mat image(17,17);
    image.randn();

    arma::mat filter(3,6,arma::fill::ones);
    
    std::cout<<"image"<<std::endl<<image<<std::endl;

    auto& scheduler = cnn::concurrency::getScheduler<void>();    
    auto fconv = cnn::get_convolute(image,2,5,scheduler);
    auto filtered = fconv(filter);
    
    std::cout<<"filtered"<<std::endl<<filtered<<std::endl;
    std::cout<<"OK";

}