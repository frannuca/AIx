#include <iostream>
#include <memory>
#include <functional>
#include <math.h>
#include <armadillo>

#include "ffnn.hpp"
#include "layer.hpp"
using namespace cnn;
int main(int argc, char** argv )
{
    size_t number_of_cells = 2;
    double c = 2.0;
    Cell::TActivation f = [c](const double& x){return 1.0/(1.0+std::exp(-c*x));};
    Cell::TActivation df = [&f,c](const double& x){return c*f(x) * (1-f(x));};
    // Cell::TActivation f = [c](const double& x){if(x<0) return 0.001*x; else return x;};
    // Cell::TActivation df = [&f,c](const double& x){if(x<0) return 0.001; else return 1.0;};
    auto floss = [](const arma::vec& x, const arma::vec& y){
                auto d = arma::sum((x-y)*(x-y));
                return d*0.5;
    };
    
    auto dfloss = [](const arma::vec& x, const arma::vec& y){return (x-y);};
    FFNN net;
    std::unique_ptr<Layer> h1(new Layer(number_of_cells,f,df));
    std::unique_ptr<Layer> h2(new Layer(number_of_cells,f,df));
    std::unique_ptr<Layer> h3(new Layer(number_of_cells,f,df));
    std::unique_ptr<Layer> h4(new Layer(number_of_cells,f,df));
    std::unique_ptr<Layer> o(new Layer(1,f,df));
    net.withInputLayer(2).withHiddenLayer(std::move(h1)).withOutputLayer(std::move(o)).withLossFunctions(floss,dfloss).Build();
    
    //data set:
    arma::vec x0({0,0});
    arma::vec x1({0,1});
    arma::vec x2({1,0});
    arma::vec x3({1,1});

    arma::vec y0({0});
    arma::vec y1({1});
    arma::vec y2({1});
    arma::vec y3({0});
    auto next = [&](){
        double err=0.0;
        err += net.forward(x0,y0);
        net.backward();

        err += net.forward(x1,y1);
        net.backward();
        
        err += net.forward(x2,y2);
        net.backward();
        
        err += net.forward(x3,y3);
        net.backward();

        std::cout<<"ERR="<<err<<std::endl;
        
    };
    
    for(int i=0;i<1000;++i) next();

    std::cout<<"(0,0)->"<<net(x0)<<" expected->"<<y0<<std::endl;
    std::cout<<"(0,1)->"<<net(x1)<<" expected->"<<y1<<std::endl;
    std::cout<<"(1,0)->"<<net(x2)<<" expected->"<<y2<<std::endl;
    std::cout<<"(1,1)->"<<net(x3)<<" expected->"<<y3<<std::endl;
    

    std::cout<<"OK"<<std::endl;
}