#include "mlp/cell.hpp"

namespace AIX{
    namespace MLP{
    Cell::Cell(std::shared_ptr<IActivation> ptr_):ptr(ptr_){

    }
    double Cell::operator()(const double& x)  {
        return ptr->f(x);
    }
    void Cell::compute(const double& x){
        _fx = ptr->f(x);
        _dfx = ptr->df(x);
    }

    std::tuple<double,double> Cell::getData(){
        return std::make_tuple(_fx,_dfx);
    }
}
}