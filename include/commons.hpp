#ifndef COMMONS_H
#define COMMONS_H
#include <iostream>
#include <armadillo>
#include <vector>
#include <utility>
namespace cnn{
    
    
    struct TrainingSample{
        arma::mat input;
        arma::mat output;
    };
    
    typedef std::vector<TrainingSample> TrainingSet;
    const double epsilon = 1e-9;
}

#endif