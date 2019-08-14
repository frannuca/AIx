#ifndef COMMONS_H
#define COMMONS_H
#include <iostream>
#include <armadillo>
#include <vector>
#include <utility>
namespace cnn{
    
    
    struct TrainingSample{
        arma::mat input;
        arma::mat output;
    };

    typedef std::vector<TrainingSample> TrainingSet;
    

    class FFNN_Params_Base{  
        public:      
        virtual ~FFNN_Params_Base(){};
    };
    class FFNN_Newton_Raphson_Params:public FFNN_Params_Base{  
        public:
        FFNN_Newton_Raphson_Params()=delete;
        FFNN_Newton_Raphson_Params(double lr):learning_rate(lr){};
        double learning_rate;
        double momentum;      
        virtual ~FFNN_Newton_Raphson_Params(){};
        
    };
    class FFNN_RSPROP_Params: public FFNN_Params_Base{
        public:
        FFNN_RSPROP_Params()=delete;
        FFNN_RSPROP_Params(double mx_lr,double min_lr,double lr_inc,double lr_dec,double lr_init):
        maximum_learning_rate(mx_lr),minimum_learning_rate(min_lr),learning_rate_increment(lr_inc),learning_rate_decrement(lr_dec),initial_learning_rate(lr_init){};
        double maximum_learning_rate;
        double minimum_learning_rate;
        double learning_rate_increment;
        double learning_rate_decrement;
        double initial_learning_rate;
        virtual ~FFNN_RSPROP_Params(){};
    };
}

#endif