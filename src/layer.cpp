#include "layer.hpp"
#include <algorithm>

namespace cnn{

    Layer::Layer(size_t number_of_cells,std::shared_ptr<IActivation> pact):Ncells(number_of_cells){
        auto cellproto = Cell(pact);
        for(size_t i=0;i<number_of_cells;++i) _cells.push_back(cellproto);
    }
    size_t Layer::size(){
        return Ncells;
    }

    arma::vec  Layer::forward(const arma::vec& x, const arma::mat& W){
        auto a1 = W.submat(0,0,arma::SizeMat(W.n_rows,x.size())) * x;
        auto b1 = W.col(x.size());
        auto s = arma::conv_to<std::vector<double>>::from( 
                            arma::conv_to<arma::colvec>::from(a1) + b1
                            );              
        inputs = s;
        int i=0;
        std::vector<double> gf,f;
        for(auto cell:_cells){
            cell.compute(s[i++]);
            double out,dout;
            std::tie(out,dout) = cell.getData();
            f.push_back(out);
            gf.push_back(dout);                        
        }

        outputs = arma::vec(f);
        doutputs = arma::vec(gf);
        f.push_back(1.0);
        outputs_1 = arma::vec(f);
        
        return outputs.get();
    }

    const arma::vec& Layer::getOutputs(bool extended){
        if(!extended){
            return outputs.get();
        }
        else{
            return outputs_1.get();
        }
        
    }

    const arma::vec& Layer::getInputs(){
        return inputs.get();
    }

    arma::vec Layer::derivatives(){        
        return doutputs.get();
    }

}