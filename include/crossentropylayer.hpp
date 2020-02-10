#ifndef CROSSENTROPYLAYER_H
#define CROSSENTROPYLAYER_H
#include <armadillo>

namespace AIX{
class CrossEntropyLayer{
    protected:        
        static arma::vec forward(const arma::vec& ycomputed, const arma::vec& yexpected);
        arma::vec grad_forward(const arma::vec& xinput,const arma::vec& xoutput);
        void backward();
    public:
        CrossEntropyLayer();
};
}

#endif