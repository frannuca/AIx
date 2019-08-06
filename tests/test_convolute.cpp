#include "commons.hpp"
#include "threadsafequeue.hpp"
#include "scheduler.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <chrono>
#include "convolution.hpp"
#include <armadillo>

int main(int, char**){
    arma::mat image(17,17);
    image.randn();

    arma::mat filter(3,6,arma::fill::ones);
    
    std::cout<<"image"<<std::endl<<image<<std::endl;

    auto scheduler = std::make_shared<cnn::concurrency::Scheduler<void>>(3);    
    auto fconv = cnn::get_convolute(image,2,5,std::move(scheduler));
    auto filtered = fconv(filter);
    
    std::cout<<"filtered"<<std::endl<<filtered<<std::endl;
    std::cout<<"OK";

}