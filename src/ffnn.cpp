#include "ffnn.hpp"

namespace cnn{
    FFNN::FFNN(){
        lr = 0.001;
    }
    
    FFNN& FFNN::withInputLayer(size_t number_of_inputs){
        _number_inputs = number_of_inputs;
        return *this;
    }

    FFNN& FFNN::withHiddenLayer(std::unique_ptr<Layer>  x){
        _layers.push_back(std::move(x));
        return *this;
    }

    FFNN& FFNN::withOutputLayer(std::unique_ptr<Layer>  x){
        _outputLayer = std::move(x);
        return *this;
    }

    void FFNN::Build(){
        _layers.push_back(std::move(_outputLayer));
        _Ws.clear();
        for(size_t i=0;i< _layers.size();++i){
            arma::mat w;
            if(i==0){
                w= arma::randn(arma::SizeMat(_layers[i]->size(),_number_inputs+1));
            }
            else{
                w= arma::randn(arma::SizeMat(_layers[i]->size(),_layers[i-1]->size()+1));
            }
            
            _Ws.push_back(std::move(w));
        }
    }

    FFNN& FFNN::withLossFunctions(std::function<double(const arma::vec&,const arma::vec&)> f,std::function<arma::vec(const arma::vec&,const arma::vec&)> df){
        _floss = f;
        _dfloss = df;
        return *this;
    }
    
    void FFNN::forward(const arma::vec& xin, const arma::vec& y){
        arma::vec x=xin;
        _input=xin;
        _output = y;

        for(size_t i=0;i <_layers.size();++i){
            x = _layers[i]->forward(x,_Ws[i]);
        } 

        //compute loss:
        _loss = _floss(x,y);
        _dloss = _dfloss(x,y);
        
    }

    void FFNN::backward(){
        arma::vec dO = (*_dloss);
        
        for(int i=_layers.size()-2;i>=0;--i){
            dO = dO % _layers[_layers.size()-1]->backward();
            if(i>0){
                arma::mat dW = dO * _layers[i-1]->getOutputs(true).t();
                dO = dO * _Ws[i];
                _Ws[i] += -lr*dW;
            }
            else{
                auto vin = arma::conv_to<std::vector<double>>::from(_input.get());
                vin.push_back(1.0);
                arma::vec in_1(vin);
                arma::mat dW = dO * in_1.t();
                dO = dO * _Ws[i];
                _Ws[i] += -lr*dW;
            }
            
        }
    }
}