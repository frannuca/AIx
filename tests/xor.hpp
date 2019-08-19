#ifndef XOR_H
#define XOR_H
#include "mlp/commons.hpp"
#include <armadillo>
using namespace AIX;

using namespace AIX;
using namespace AIX::MLP;
class XORDS{
    public:
    static TrainingSet GetXORSet(){
            arma::vec x0({0,0});
            arma::vec x1({0,1});
            arma::vec x2({1,0});
            arma::vec x3({1,1});

            arma::vec y0({0});
            arma::vec y1({1});
            arma::vec y2({1});
            arma::vec y3({0});
            
            TrainingSet tset;
            tset.push_back(TrainingSample {x0,y0});
            tset.push_back(TrainingSample {x1,y1});
            tset.push_back(TrainingSample {x2,y2});
            tset.push_back(TrainingSample {x3,y3});

            

            return tset;
    }
};
//data set:
    
#endif