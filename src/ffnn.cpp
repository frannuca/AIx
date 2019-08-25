#include "mlp/ffnn.hpp"
#include "concurrency/scheduler.hpp"

namespace AIX{namespace MLP{


    #pragma region // Implementation of FFNN methods
    FFNN::FFNN(){      
    }
    
    void FFNN::withInputLayer(size_t number_of_inputs){
        _number_inputs = number_of_inputs;
    }

    void FFNN::withHiddenLayer(std::unique_ptr<Layer>  x){
        _layers.push_back(std::move(x));
    }

    void FFNN::withOutputLayer(std::unique_ptr<Layer>  x){
        _outputLayer = std::move(x);
    }
    

    void FFNN::withLossFunctions(std::function<double(const arma::vec&,const arma::vec&)> f,std::function<arma::vec(const arma::vec&,const arma::vec&)> df){
        _floss = f;
        _dfloss = df;
      
    }
    
    double FFNN::forward(const arma::vec& xin, const arma::vec& y) const {
        arma::vec x=xin;
        _input=xin;
        std::vector<double> auxin = arma::conv_to<std::vector<double>>::from(xin);
        auxin.push_back(1);
        _input_1 = arma::vec(auxin);
        _output = y;

        for(size_t i=0;i <_layers.size();++i){
            x = _layers[i]->forward(x,_Ws[i],&y);
        } 

        //compute loss:
        _loss = _floss(x,y);
        _dloss = _dfloss(x,y);

        return _loss.get();
        
    }

    arma::vec FFNN::operator()(const arma::vec& x) const{       
        arma::vec s = x;
        for(size_t i=0;i <_layers.size();++i){
            s = _layers[i]->forward(s,_Ws[i],nullptr);
        } 
        return s;
    }

    FFNN::~FFNN(){};

    double FFNN::train(const TrainingSet& trainingset, size_t niter,double tol) const{
        
        //auto& scheduler = Concurrency::getScheduler<double>();

        double totalerr=0; 
        for(size_t n=0;n<niter;++n){
           totalerr=0; 
            
            for(auto x:trainingset){                
                totalerr += forward(x.input.col(0),x.output.col(0));
                backward();
            };


            
                       
            update(totalerr);
        std::cout<<"Iteration "<<n<<" Error="<<totalerr<<std::endl;   
        if(totalerr < tol){
            break;
        }             
        }        
        return totalerr;
    }
}}