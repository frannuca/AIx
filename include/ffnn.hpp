#ifndef FFNN_H
#define FFNN_H
#include "layer.hpp"
#include <memory>
#include <functional>
#include <armadillo>

namespace cnn{
    class FFNN{
        private:
            std::vector<std::unique_ptr<Layer>> _layers;
            std::unique_ptr<Layer> _outputLayer;
            std::function<double(const arma::vec&,const arma::vec&)> _floss;
            std::function<arma::vec(const arma::vec&,const arma::vec&)> _dfloss;
            std::vector<arma::mat> _Ws;
            size_t _number_inputs;
            boost::optional<double> _loss;
            boost::optional<arma::vec> _dloss;
            boost::optional<arma::vec> _input;
            boost::optional<arma::vec> _input_1;
            boost::optional<arma::vec> _output;
            double lr;

        public:
            FFNN();
            FFNN& withInputLayer(size_t number_of_inputs);
            FFNN& withHiddenLayer(std::unique_ptr<Layer>);
            FFNN& withOutputLayer(std::unique_ptr<Layer>);
            FFNN& withLossFunctions(std::function<double(const arma::vec&,const arma::vec&)> loss,std::function<arma::vec(const arma::vec&, const arma::vec&)>grad_loss);
            void Build();
            double forward(const arma::vec& xin, const arma::vec& y);
            void backward();

            arma::vec operator()(const arma::vec& x);
    };
}
#endif