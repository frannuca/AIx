#ifndef INETWORK_H
#define INETWORK_H
#include <memory>
#include <armadillo>
#include "commons.hpp"

namespace AIX{
    namespace MLP{
    
    class INetwork{
        public:
        virtual double forward(const arma::vec& xin, const arma::vec& y) const = 0;
        virtual void backward() const = 0;
        virtual void update(double totalerror) const = 0;
        virtual arma::vec operator()(const arma::vec& x) const = 0;         
        virtual double train(const TrainingSet& trainingset,size_t niter,double tol) const = 0;
        
        virtual ~INetwork(){};
    };

}
}
#endif