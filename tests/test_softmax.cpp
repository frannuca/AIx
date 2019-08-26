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

using namespace AIX;
using namespace AIX::MLP;

int main(int argc, char** argv )
{
    size_t number_of_cells = 2;
    double c = 1.0;
    std::shared_ptr<IActivation> hyper(new HyperbolicTangent(c));
    std::shared_ptr<IActivation> sigmoid(new Sigmoid(c));
    std::shared_ptr<IActivation> relu(new ReLU(0.01,1.0));
    std::shared_ptr<IActivation> exponential(new Exponential(1.0));    
    


    AIX::CrossEntropyLoss floss2;
    FFNN_RSPROP_Params rsparam(0.2,0.001,1.2,0.5,0.05);
    FFNN_Newton_Raphson_Params newtonparams(0.2);
    
    FFNNBuilder net(FFNN_TYPES::RSPROP,&rsparam);
    
    std::unique_ptr<INetwork> ffnn = net.withInputLayer(2)
                                        .withHiddenLayer(number_of_cells,hyper)                                        
                                        //.withHiddenLayer(number_of_cells,sigmoid)                                        
                                        .withSoftmaxOutputLayer(4)
                                        .withLossFunctions(&floss2)
                                        .Build();
                
    //data set:
    
    TrainingSet tset = XORDS::GetXORSoftmaxSet();
    
    ffnn->train(tset,100,0.01);
    for(auto& sample:tset){
        std::cout<<((arma::mat)sample.input).t()<<"->"<<std::endl<<arma::mat((*ffnn)(sample.input)).t()<<std::endl<<((arma::mat)sample.output).t()
        <<std::endl<<"-----------------"<<std::endl;
    }
   
    

    std::cout<<"OK"<<std::endl;
}