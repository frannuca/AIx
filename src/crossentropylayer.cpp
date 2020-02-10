#include "crossentropylayer.hpp"
#include "constants.hpp"
#include <armadillo>

namespace AIX{
    CrossEntropyLayer::CrossEntropyLayer(){}

    arma::vec CrossEntropyLayer::forward(const arma::vec& ycomputed, const arma::vec& yexpected){
        arma::vec ln = arma::log(ycomputed);

        double o = arma::sum(yexpected * ln);
        return arma::vec({o});
    }

    arma::vec CrossEntropyLayer::grad_forward(const arma::vec& xinput,const arma::vec& xoutput){
            return xinput*(1.0/(xoutput+epsilon));
    }
    
    void CrossEntropyLayer::backward(){
        
    }

    
}
