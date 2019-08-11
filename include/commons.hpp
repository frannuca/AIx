#ifndef COMMONS_H
#define COMMONS_H
#include <iostream>
#include <armadillo>
#include <vector>
#include <utility>
namespace cnn{
    typedef std::pair<arma::mat,arma::mat> TrainingSample;
    typedef std::vector<TrainingSample> TrainingSet;

    const double epsilon = 1e-9;
}

#endif