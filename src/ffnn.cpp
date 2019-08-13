#include "ffnn.hpp"

namespace cnn{
    FFNN::FFNN(){
        lr = 0.1;
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
                w= arma::randu(arma::SizeMat(_layers[i]->size(),_number_inputs+1))*std::sqrt(1.0/_number_inputs);
            }
            else{
                w= arma::randu(arma::SizeMat(_layers[i]->size(),_layers[i-1]->size()+1))*std::sqrt(1.0/_layers[i]->size());
            }
            //std::cout<<"W["<<i<<"]"<<w<<std::endl;
            w.col(w.n_cols-1) = arma::vec(w.n_rows)*0.0;
            _Ws.push_back(std::move(w));
        }
        // std::string dummy;
        // std::cin>>dummy;
    }

    FFNN& FFNN::withLossFunctions(std::function<double(const arma::vec&,const arma::vec&)> f,std::function<arma::vec(const arma::vec&,const arma::vec&)> df){
        _floss = f;
        _dfloss = df;
        return *this;
    }
    
    double FFNN::forward(const arma::vec& xin, const arma::vec& y){
        arma::vec x=xin;
        _input=xin;
        std::vector<double> auxin = arma::conv_to<std::vector<double>>::from(xin);
        auxin.push_back(1);
        _input_1 = arma::vec(auxin);
        _output = y;

        for(size_t i=0;i <_layers.size();++i){
            x = _layers[i]->forward(x,_Ws[i]);
            //std::cout<<"output["<<i<<"]"<<x.t()<<std::endl;
            //std::string dummy;
            //std::cin>>dummy;
        } 

        //compute loss:
        _loss = _floss(x,y);
        _dloss = _dfloss(x,y);

        return _loss.get();
        
    }

    void FFNN::backward(){        
        arma::mat delta = (*_dloss) % _layers[_layers.size()-1]->derivatives();

        for(int i=_layers.size()-1;i>=0;--i){         
                arma::vec x;   
                if(i>0){
                    x = _layers[i-1]->getOutputs(true);
                }
                else{
                    x=_input_1.get();
                }
                arma::mat dW = delta * x.t() ;                                                                
                _Ws[i] += -lr*dW;
                auto Wv = _Ws[i].submat(0,0,arma::SizeMat(_Ws[i].n_rows,_Ws[i].n_cols-1));

                if(i>0){
                    delta =  (delta.t() *Wv).t() % _layers[i-1]->derivatives();
                }
                
            
        }
        
    }

    arma::vec FFNN::operator()(const arma::vec& x){       
        arma::vec s = x;
        for(size_t i=0;i <_layers.size();++i){
            s = _layers[i]->forward(s,_Ws[i]);
        } 
        return s;
    }
}