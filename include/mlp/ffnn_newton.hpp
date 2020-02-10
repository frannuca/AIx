#ifndef FFNN_NEWTON_H
#define FFNN_NEWTON_H
#include "layer.hpp"
#include <memory>
#include <functional>
#include <armadillo>
#include "inetwork.hpp"
#include "ffnn.hpp"

namespace AIX{
    namespace MLP{
    class FFNN_NEWTON: public FeedForwardNN{
        
        public:
        const double lr;
        explicit FFNN_NEWTON(double learning_rate);
        virtual void backward() const override;
        virtual void update(double totalerror) const override;
        virtual ~FFNN_NEWTON() override;
    };
}
}
#endif