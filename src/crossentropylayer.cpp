#include "crossentropylayer.hpp"
#include "constants.hpp"
#include <armadillo>

namespace AIX{
    CrossEntropyLayer::CrossEntropyLayer(){}

    arma::vec CrossEntropyLayer::forward(const arma::vec& xinput,const arma::vec& xoutput){
        arma::vec ln = arma::log(xinput);

        double o = arma::sum(xinput*ln);
        return arma::vec({o});
    }

    arma::vec CrossEntropyLayer::grad_forward(const arma::vec& xinput,const arma::vec& xoutput){
            return xinput*(1.0/(xoutput+epsilon));
    }
    
    void CrossEntropyLayer::backward(){
        
    }

    
}
