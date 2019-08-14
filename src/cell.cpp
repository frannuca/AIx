#include "mlp/cell.hpp"

namespace cnn{
    Cell::Cell(std::shared_ptr<IActivation> ptr_):ptr(ptr_){

    }

    void Cell::compute(const double& x){
        _fx.reset(ptr->f(x));
        _dfx.reset(ptr->df(x));        

    }

    std::tuple<double,double> Cell::getData(){
        return std::make_tuple(_fx.get(),_dfx.get());
    }
}