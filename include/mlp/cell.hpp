#ifndef CELL_H
#define CELL_H
#include <functional>
#include <boost/optional.hpp>
#include "../activations.hpp"
#include <memory>

namespace AIX{
    namespace MLP{
    class Cell{                                
        private:      
            std::shared_ptr<IActivation> ptr;      
            double _fx;
            double _dfx;
                        
        public:
            
            Cell()=delete;
            explicit Cell(std::shared_ptr<IActivation> ptr);
            double operator()(const double& x);
            void compute(const double& x);
            std::tuple<double,double> getData();
    };
}
}
#endif