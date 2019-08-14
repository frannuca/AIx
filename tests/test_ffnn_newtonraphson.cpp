#include <iostream>
#include <memory>
#include <functional>
#include <math.h>
#include <armadillo>
#include "commons.hpp"
#include "inetwork.hpp"
#include "ffnn.hpp"
#include "ffnn_newton.hpp"
#include "ffnnbuilder.hpp"
#include "activations.hpp"
#include "layer.hpp"

using namespace cnn;
int main(int argc, char** argv )
{
    size_t number_of_cells = 2;
    double c = 2.0;
    std::shared_ptr<IActivation> sigmoid(new Sigmoid(c));
    std::shared_ptr<IActivation> relu(new ReLU(0.001,2.0));
    std::shared_ptr<IActivation> fact = sigmoid;
    auto floss = [](const arma::vec& x, const arma::vec& y){
                auto d = arma::sum((x-y)*(x-y));
                return d*0.5;
    };
    
    auto dfloss = [](const arma::vec& x, const arma::vec& y){return (x-y);};
    cnn::FFNN_Newton_Raphson_Params newtonparams(0.33);
    
    FFNNBuilder net(FFNN_TYPES::NEWTON_RAPHSON,&newtonparams);
    
    std::unique_ptr<INetwork> ffnn = net.withInputLayer(2)
                                        .withHiddenLayer(number_of_cells,fact)
                                        .withOutputLayer(1,fact)
                                        .withLossFunctions(floss,dfloss)
                                        .Build();
                
    //data set:
    arma::vec x0({0,0});
    arma::vec x1({0,1});
    arma::vec x2({1,0});
    arma::vec x3({1,1});

    arma::vec y0({0});
    arma::vec y1({1});
    arma::vec y2({1});
    arma::vec y3({0});
    
    cnn::TrainingSet tset;
    tset.push_back(TrainingSample {x0,y0});
    tset.push_back(TrainingSample {x1,y1});
    tset.push_back(TrainingSample {x2,y2});
    tset.push_back(TrainingSample {x3,y3});
    
    ffnn->train(tset,1000,0.01);

    std::cout<<"(0,0)->"<<(*ffnn)(x0)<<" expected->"<<y0<<std::endl;
    std::cout<<"(0,1)->"<<(*ffnn)(x1)<<" expected->"<<y1<<std::endl;
    std::cout<<"(1,0)->"<<(*ffnn)(x2)<<" expected->"<<y2<<std::endl;
    std::cout<<"(1,1)->"<<(*ffnn)(x3)<<" expected->"<<y3<<std::endl;
    

    std::cout<<"OK"<<std::endl;
}