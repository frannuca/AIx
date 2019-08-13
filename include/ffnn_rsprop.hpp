#ifndef FFNN_RSPROP_H
#define FFNN_RSPROP_H
#include "layer.hpp"
#include <memory>
#include <functional>
#include <armadillo>
#include <boost/optional.hpp>
#include "inetwork.hpp"
#include "ffnn.hpp"
#include <armadillo>

namespace cnn{
    class FFNN_RSPROP: public FFNN{
        private:
        mutable std::vector<std::vector<arma::mat>> _dWs;
        public:
        using FFNN::FFNN;
        virtual void backward() const override;
        void init() override;
        virtual ~FFNN_RSPROP() override{};
    };
}

#endif