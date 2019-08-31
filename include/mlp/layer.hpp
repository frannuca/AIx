#ifndef LAYER_H
#define LAYER_H
#include <functional>
#include <armadillo>
#include <memory>
#include "commons.hpp"
#include "cell.hpp"
#include "../activations.hpp"
#include <boost/optional.hpp>

namespace AIX{
    namespace MLP{
    class Layer{
        protected:
            bool isactivation_relu;            
            size_t Ncells;
            std::vector<Cell> _cells;
            arma::vec inputs;
            arma::vec outputs;
            arma::vec outputs_1;
            arma::vec doutputs;
            
        public:
            Layer() = delete;
            Layer(size_t number_of_cells,std::shared_ptr<IActivation> ptract);
            virtual ~Layer(){};

            virtual arma::vec operator()(const arma::vec& x,const arma::mat& W) const;
            virtual arma::vec forward(const arma::vec& x, const arma::mat& W,const arma::vec* out = nullptr );
            virtual arma::vec derivatives();
            virtual const arma::vec& getOutputs(bool extended = false);
            virtual const arma::vec& getInputs();
            virtual size_t size();
            virtual bool isActivationReLU() const;
            
    };
}
}
#endif
