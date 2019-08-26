#ifndef XOR_H
#define XOR_H
#include "mlp/commons.hpp"
#include <armadillo>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

using namespace AIX;

using namespace AIX;
using namespace AIX::MLP;
using namespace std;

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

    static TrainingSet GetXORSoftmaxSet(){
            
            // First create an instance of an engine.
                random_device rnd_device;
                // Specify the engine and distribution.
                mt19937 mersenne_engine {rnd_device()};  // Generates random integers
                uniform_real_distribution<double> dist (-1,1);
                
                auto gen = [&dist, &mersenne_engine](){
                                return dist(mersenne_engine);
                        };

                

            TrainingSet tset;
            for(int i=0;i<10;++i){
                    vector<double> x(2);
                    generate(begin(x), end(x), gen);
                    vector<double> y(4,0.0);
                    if(x[0]>0 && x[1]>0){
                            y[0]=1;
                    }
                    else if(x[0]>0 && x[1]<0){
                            y[1]=1;
                    }
                    else if(x[0]<0 && x[1]<0){
                            y[2]=1;
                    }
                    else{
                            y[3]=1;
                    }

                    tset.push_back(TrainingSample {x,y});
            }                                   

            return tset;
    }
};
//data set:
    
#endif