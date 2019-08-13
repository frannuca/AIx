#include "ffnn.hpp"

namespace cnn{
    FFNN::FFNN(){
        lr = 0.01;
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
                w= arma::randu(arma::SizeMat(_layers[i]->size(),_number_inputs+1))*0.1;
            }
            else{
                w= arma::randu(arma::SizeMat(_layers[i]->size(),_layers[i-1]->size()+1))*0.1;
            }
            //std::cout<<"W["<<i<<"]"<<w<<std::endl;

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
        arma::vec dOo = (*_dloss);
        arma::mat dO = arma::conv_to<arma::mat>::from( dOo % _layers[_layers.size()-1]->backward());
        for(int i=_layers.size()-1;i>=0;--i){            
            if(i>0){
                arma::mat paux= arma::conv_to<arma::mat>::from(_layers[i-1]->getOutputs(true)).t();
                int xx = paux.size();
                arma::mat dW = dO * paux ;
                int wrow = _Ws[i].n_rows;
                int wcol = _Ws[i].n_cols;
                int dorow = dO.size();         
                auto auxaa = _Ws[i].submat(0,0,arma::SizeMat(_Ws[i].n_rows,_Ws[i].n_cols-1));
                arma::mat dx = dO.t();
                arma::mat dxW = (dx * auxaa);
                dO = dxW.t();
                //std::cout<<"dW["<<i<<"]"<<std::endl<<dW<<std::endl;
                //std::string dummy;
                //std::cin>>dummy;
                _Ws[i] += -lr*dW;
            }
            else{
                auto vin = arma::conv_to<std::vector<double>>::from(_input.get());
                vin.push_back(1.0);
                arma::mat in_1(vin);
                arma::mat dW = dO * in_1.t();
                dO = (dO.t() * _Ws[i].submat(0,0,arma::SizeMat(_Ws[i].n_rows,_Ws[i].n_cols-1))).t();
                _Ws[i] += -lr*dW;
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