#include <iostream>
#include <memory>
#include <functional>
#include <math.h>
#include <armadillo>
#include "mlp/commons.hpp"
#include "mlp/inetwork.hpp"
#include "mlp/ffnn.hpp"
#include "mlp/ffnn_newton.hpp"
#include "mlp/ffnnbuilder.hpp"
#include "activations.hpp"
#include "mlp/layer.hpp"
#include "xor.hpp"
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
   
    cnn::TrainingSet tset = XORDS::GetXORSet();
    ffnn->train(tset,1000,0.01);

    std::cout<<"(0,0)->"<<(*ffnn)(tset[0].input)<<" expected->"<<tset[0].output<<std::endl;
    std::cout<<"(0,1)->"<<(*ffnn)(tset[1].input)<<" expected->"<<tset[1].output<<std::endl;
    std::cout<<"(1,0)->"<<(*ffnn)(tset[2].input)<<" expected->"<<tset[2].output<<std::endl;
    std::cout<<"(1,1)->"<<(*ffnn)(tset[3].input)<<" expected->"<<tset[3].output<<std::endl;
    
    

    std::cout<<"OK"<<std::endl;
}