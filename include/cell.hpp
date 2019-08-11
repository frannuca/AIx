#ifndef CELL_H
#define CELL_H
#include <functional>
#include <boost/optional.hpp>

namespace cnn{
    class Cell{
        public:
            typedef std::function<double(const double&)> TActivation;
                        
        private:            
            boost::optional<double> _fx;
            boost::optional<double> _dfx;
            
            TActivation _f;
            TActivation _df;

        public:
            
            Cell()=delete;
            explicit Cell(TActivation f, TActivation df);

            void compute(const double& x);
            std::tuple<double,double> getData();
    };
}
#endif