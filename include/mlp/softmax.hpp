#ifndef SOFTMAX_H
#define SOFTMAX_H

#include "layer.hpp"
#include <armadillo>

namespace AIX{
  namespace MLP{
    class Softmax:public Layer{
      
      public:
        Softmax() = delete;
        Softmax(size_t number_of_classes_);
        arma::vec forward(const arma::vec& x, const arma::mat& W,const arma::vec* out) override;
        virtual arma::vec operator()(const arma::vec& x,const arma::mat& W) const override;
    };
  }
    
}
#endif