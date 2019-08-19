#ifndef CROSSENTROPYLAYER_H
#define CROSSENTROPYLAYER_H
#include <armadillo>

namespace AIX{
class CrossEntropyLayer{
    protected:        
        arma::vec forward(const arma::vec& xinput,const arma::vec& xoutput);
        arma::vec grad_forward(const arma::vec& xinput,const arma::vec& xoutput);
        void backward();
    public:
        CrossEntropyLayer();
};
}

#endif