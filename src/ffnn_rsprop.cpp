#include "mlp/ffnn_rsprop.hpp"
#include <math.h>
#include <limits>

namespace cnn{

    void FFNN_RSPROP::init() {
        for(auto&w :_Ws){
            std::vector<arma::mat> arr;                                   
            _dWs.push_back(std::vector<arma::mat>());               
            _lr.push_back(arma::mat(w.n_rows,w.n_cols,arma::fill::ones)*_lr0);
            _Ws_before = _Ws;
            _error[0] = std::numeric_limits<double>::infinity();
            _error[1] = std::numeric_limits<double>::infinity();
        }
    }
    
    FFNN_RSPROP::FFNN_RSPROP(double lrplus,double lrminus,double maxlr, double minlr,double initial_lr):
    _lrplus(lrplus),_lrminus(lrminus),_maxlr(maxlr),_minlr(minlr),_lr0(initial_lr) {}

    void FFNN_RSPROP::backward() const{        

        arma::mat delta = (*_dloss) % _layers[_layers.size()-1]->derivatives();

        for(int i=_layers.size()-1;i>=0;--i){         
                arma::vec x;   
                if(i>0){
                    x = _layers[i-1]->getOutputs(true);
                }
                else{
                    x=_input_1.get();
                }
                arma::mat dW = delta * x.t();
                _dWs_accum[i]+= dW;

                auto Wv = _Ws[i].submat(0,0,arma::SizeMat(_Ws[i].n_rows,_Ws[i].n_cols-1));

                if(i>0){
                    delta =  (delta.t() *Wv).t() % _layers[i-1]->derivatives();
                }                            
        }        
    }

    void FFNN_RSPROP::update(double totalerror) const{
            
            if(_error[0]==std::numeric_limits<double>::infinity()){
            _error[0] = totalerror;
            }
            else if(_error[1]==std::numeric_limits<double>::infinity()){
                _error[1] = totalerror;
            }
            else{
                _error[0] = _error[1];
                _error[1] = totalerror;
            }

            for(int l=0;l<_layers.size();++l){

                    switch(_dWs[l].size())
                    {
                        case(0):
                            _dWs[l].push_back(_dWs_accum[l]);
                            break;
                        case(1):
                            _dWs[l].push_back(_dWs_accum[l]);
                            break;
                        default:
                            _dWs[l][0]=_dWs[l][1];
                            _dWs[l][1] = _dWs_accum[l];
                            break;
                    };

                if(_dWs[l].size()==2){
                    arma::mat signs = _dWs[l][0] % _dWs[l][1];
                    for(int i=0;i<signs.n_rows;++i){
                        for(int j=0;j<signs.n_cols;++j){
                            if(signs(i,j)>0.0){
                                _lr[l](i,j) = std::min(_lr[l](i,j)*_lrplus,_maxlr);                            
                            }
                            else if(signs(i,j)<0.0){
                                    _lr[l](i,j) = std::max(_lr[l](i,j)*_lrminus,_minlr);                                    

                                    if(_error[1]>_error[0]){
                                        _Ws[l] = _Ws_before[l];
                                    }
                                    _dWs_accum[l] *= 0.0;                                   
                            }
                            
                        }
                    } 
                }
                 _Ws[l] -= _lr[l] % _dWs_accum[l];    
                _dWs_accum[l] *= 0.0;    
                _Ws_before[l] = _Ws[l];                          
            }            
    }
}