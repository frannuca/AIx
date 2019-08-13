#ifndef FFNNBUILDER_H
#define FFNNBUILDER_H
#include "layer.hpp"
#include <memory>
#include <functional>
#include <armadillo>
#include "inetwork.hpp"
#include "ffnn.hpp"

namespace cnn{
     enum class FFNN_TYPES{
        NEWTON_RAPHSON,
        NONE
    };

   class FFNNBuilder{
       private:
       std::unique_ptr<FFNN> _instance;
       public:
        FFNNBuilder()=delete;
        FFNNBuilder(FFNN_TYPES);
        FFNNBuilder& withInputLayer(size_t number_of_inputs);
        FFNNBuilder& withHiddenLayer(size_t ncells, std::shared_ptr<IActivation> fact);
        FFNNBuilder& withOutputLayer(size_t ncells, std::shared_ptr<IActivation> fact);
        FFNNBuilder& withLossFunctions(std::function<double(const arma::vec&,const arma::vec&)> loss,
                                       std::function<arma::vec(const arma::vec&, const arma::vec&)>grad_loss);
        std::unique_ptr<INetwork> Build();                        
   };
}
#endif