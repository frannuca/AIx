#include "ffnn_newton.hpp"

namespace cnn{
    void FFNN_NEWTON::backward() const{        
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
    FFNN_NEWTON::~FFNN_NEWTON(){

    }
}