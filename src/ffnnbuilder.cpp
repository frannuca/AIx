#include "ffnnbuilder.hpp"
#include "ffnn_newton.hpp"
#include "ffnn_rsprop.hpp"
namespace cnn{
    #pragma endregion //FFNN implementation
    FFNNBuilder::FFNNBuilder(FFNN_TYPES typ,const FFNN_Params_Base* params){
        FFNN* ptr=nullptr;
        if(typ == FFNN_TYPES::NEWTON_RAPHSON)
        {        
            const FFNN_Newton_Raphson_Params* p1 = dynamic_cast<const FFNN_Newton_Raphson_Params*>(params);
            if(p1==nullptr){
                throw "Invalid parameters passed to constuct the FFNN Newton Raphson training algorithm.";
            }

            ptr = new FFNN_NEWTON(p1->learning_rate);
        }
        else if(typ == FFNN_TYPES::RSPROP){
            const FFNN_RSPROP_Params* p2 = dynamic_cast<const FFNN_RSPROP_Params*>(params);
            if(p2==nullptr){
                throw "Invalid parameters passed to constuct the FFNN RSProp training algorithm.";
            }

            ptr = new FFNN_RSPROP(p2->learning_rate_increment,p2->learning_rate_decrement,p2->maximum_learning_rate,p2->minimum_learning_rate,p2->initial_learning_rate);    
        }
        else{
            throw "Invalid FFNN_TYPE";
        }    
                    

        this->_instance.reset(ptr);
    }
    FFNNBuilder& FFNNBuilder::withInputLayer(size_t number_of_inputs){
        _instance->withInputLayer(number_of_inputs);
        return *this;
    }
    FFNNBuilder& FFNNBuilder::withHiddenLayer(size_t ncells, std::shared_ptr<IActivation> fact){
        std::unique_ptr<Layer> p(new Layer(ncells,fact));
        _instance->withHiddenLayer(std::move(p));
        return *this;
    }
    FFNNBuilder& FFNNBuilder::withOutputLayer(size_t ncells, std::shared_ptr<IActivation> fact){
       std::unique_ptr<Layer> p(new Layer(ncells,fact));
       _instance->withOutputLayer(std::move(p));
        return *this;
    }
    FFNNBuilder& FFNNBuilder::withLossFunctions(std::function<double(const arma::vec&,const arma::vec&)> loss,
                                                std::function<arma::vec(const arma::vec&, const arma::vec&)>grad_loss){
        _instance->withLossFunctions(loss,grad_loss);
        return *this;         
    }

    std::unique_ptr<INetwork> FFNNBuilder::Build(){
        auto& _layers =  _instance->_layers;
        auto& _Ws = _instance->_Ws;
        auto& _dWs_accum = _instance->_dWs_accum;
        auto& _number_inputs = _instance->_number_inputs;
        auto& _outputLayer = _instance->_outputLayer;
        _layers.push_back(std::move(_outputLayer));
        _Ws.clear();
        for(size_t i=0;i< _instance->_layers.size();++i){
            arma::mat w;
            if(i==0){
                w= arma::randu(arma::SizeMat(_layers[i]->size(),_number_inputs+1))*std::sqrt(1.0/_number_inputs);
            }
            else{
                w= arma::randu(arma::SizeMat(_layers[i]->size(),_layers[i-1]->size()+1))*std::sqrt(1.0/_layers[i]->size());
            }           
            w.col(w.n_cols-1) = arma::vec(w.n_rows)*0.0;
            _dWs_accum.push_back(arma::mat(w.n_rows,w.n_cols,arma::fill::zeros));
            _Ws.push_back(std::move(w));            
        }
        _instance->init();
        return std::move(_instance);
    }
}