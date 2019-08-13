#ifndef LAYER_H
#define LAYER_H
#include <functional>
#include <armadillo>
#include "commons.hpp"
#include "cell.hpp"
#include <boost/optional.hpp>

namespace cnn{
    class Layer{
        private:
            size_t Ncells;
            std::vector<Cell> _cells;
            boost::optional<arma::vec> inputs;
            boost::optional<arma::vec> outputs;
            boost::optional<arma::vec> outputs_1;
            boost::optional<arma::vec> doutputs;

        public:
            Layer() = delete;
            Layer(size_t number_of_cells,Cell::TActivation f, Cell::TActivation df);

            arma::vec forward(const arma::vec& x, const arma::mat& W);
            arma::vec derivatives();
            const arma::vec& getOutputs(bool extended = false);
            const arma::vec& getInputs();
            size_t size();
            
    };
}
#endif
