#include "cell.hpp"

namespace cnn{
    Cell::Cell(Cell::TActivation f, Cell::TActivation fgrad):_f(f),_df(fgrad){}

    void Cell::compute(const double& x){
        _fx.reset(_f(x));
        _dfx.reset(_df(x));        

    }

    std::tuple<double,double> Cell::getData(){
        return std::make_tuple(_fx.get(),_dfx.get());
    }
}