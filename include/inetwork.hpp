#ifndef INETWORK_H
#define INETWORK_H
#include <armadillo>
#include "commons.hpp"

namespace cnn{
    class INetwork{
        public:
        virtual double forward(const arma::vec& xin, const arma::vec& y) const = 0;
        virtual void backward() const = 0;
        virtual arma::vec operator()(const arma::vec& x) const = 0;         
        virtual void train(const TrainingSet& trainingset,size_t niter) const = 0;
        
        virtual ~INetwork(){};
    };
}
#endif