#ifndef FFNN_NEWTON_H
#define FFNN_NEWTON_H
#include "layer.hpp"
#include <memory>
#include <functional>
#include <armadillo>
#include "inetwork.hpp"
#include "ffnn.hpp"

namespace cnn{
    class FFNN_NEWTON: public FFNN{
        public:
        using FFNN::FFNN;
        virtual void backward() const override;
        virtual ~FFNN_NEWTON() override;
    };
}

#endif