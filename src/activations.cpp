#include "activations.hpp"
#include <math.h>

namespace AIX{
    Sigmoid::Sigmoid(double c_):c(std::abs(c_)){}

    double Sigmoid::f(const double& x){
        return 1.0/(1.0+std::exp(-c*x));
    }

    double Sigmoid::df(const double& x){
        return c*f(x) * (1-f(x));
    }

    Exponential::Exponential(double c_):c(c_){}

    double Exponential::f(const double& x){
        return std::exp(c*x);
    }

    double Exponential::df(const double& x){
        return c* std::exp(c*x);
    }

    HyperbolicTangent::HyperbolicTangent(double c_):c(std::abs(c_)){}

    double HyperbolicTangent::f(const double& x){
        return (std::exp(c*x)-std::exp(-c*x))/(std::exp(c*x)+std::exp(-c*x));
    }

    double HyperbolicTangent::df(const double& x){
        double a = f(x);
        return c*(1.0-a*a);
    }

    ReLU::ReLU(double leak_,double slope_):leak(std::abs(leak_)),slope(std::abs(slope_)){}
    double ReLU::f(const double& x){
        if(x<0){
            return leak*x;
        }
        else{
            return slope*x;
        }        
    }

    double ReLU::df(const double& x){
         if(x<0){
            return leak;
        }
        else{
            return slope;
        }        
    }
}