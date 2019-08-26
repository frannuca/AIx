#ifndef LOSS_H
#define LOSS_H
#include <armadillo>

namespace AIX{
    class LossFunction{
        public:
        virtual double loss(const arma::vec& xin, const arma::vec& target) const = 0;
        virtual arma::vec derivative(const arma::vec& xin, const arma::vec& target) const = 0;
        virtual ~LossFunction(){};

    };

    class LeastSquaresLoss:public LossFunction{
        public:
        virtual double loss(const arma::vec& xin, const arma::vec& target) const override;
        virtual arma::vec derivative(const arma::vec& xin, const arma::vec& target) const override;
        virtual ~LeastSquaresLoss() override {};

    };

    class CrossEntropyLoss:public LossFunction{
        public:
        virtual double loss(const arma::vec& xin, const arma::vec& target) const override;
        virtual arma::vec derivative(const arma::vec& xin, const arma::vec& target) const override;
        virtual ~CrossEntropyLoss() override {};       

    };
}
#endif