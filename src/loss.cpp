#include "loss.hpp"
#include <math.h>

namespace AIX{

    double LeastSquaresLoss::loss(const arma::vec& x, const arma::vec& y) const{
            auto d = arma::sum((x-y)%(x-y));
            return d*0.5;
    }

    arma::vec LeastSquaresLoss::derivative(const arma::vec& x, const arma::vec& y) const{
            return (x-y);
    }
    

    double CrossEntropyLoss::loss(const arma::vec& x, const arma::vec& y) const{
            double l=0;
            for(int i=0;i<x.size();++i){                
                if(y(i)== 1)
                    return -std::log(x(i));                                
            }            
            throw "invalid class";
            
    }

    
    arma::vec CrossEntropyLoss::derivative(const arma::vec& x, const arma::vec& y) const{
            arma::vec l(x.size(),arma::fill::zeros);
            int iclass = -1;
            for(int i=0;i<y.size();++i){
                if(y(i)==1){
                    iclass = i;
                    break;
                }
            }
            
             for(int i=0;i<y.size();++i) l(i) = -y(iclass)/(x(iclass));               
        
         return l;
        
    }
}