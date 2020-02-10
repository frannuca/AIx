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

namespace AIX{
    namespace MLP{
    class FFNN_RSPROP: public FeedForwardNN{
        private:
        mutable std::vector<std::vector<arma::mat>> _dWs;        
        mutable std::vector<arma::mat> _Ws_before;
        mutable std::vector<arma::mat> _lr;
        mutable double  _error[2];
        

        public:
        const double _lrplus;
        const double _lrminus;
        const double _maxlr;
        const double _minlr;
        const double _lr0;

        FFNN_RSPROP()=delete;
        FFNN_RSPROP(double lrplus,double lrminus,double maxlr, double minlr,double initial_lr);
        virtual void backward() const override;
        virtual void update(double totalerror) const override;
        void init() override;
        virtual ~FFNN_RSPROP() override{};
    };
}
}

#endif