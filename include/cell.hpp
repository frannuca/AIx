#ifndef CELL_H
#define CELL_H
#include <functional>
#include <boost/optional.hpp>
#include "activations.hpp"
#include <memory>

namespace cnn{
    class Cell{                                
        private:      
            std::shared_ptr<IActivation> ptr;      
            boost::optional<double> _fx;
            boost::optional<double> _dfx;
                        
        public:
            
            Cell()=delete;
            explicit Cell(std::shared_ptr<IActivation> ptr);

            void compute(const double& x);
            std::tuple<double,double> getData();
    };
}
#endif