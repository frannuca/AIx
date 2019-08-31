#include "mlp/layer.hpp"
#include <algorithm>
#include <utility>
#include <type_traits>
#include "utils.hpp"

namespace AIX{namespace MLP{

    Layer::Layer(size_t number_of_cells,std::shared_ptr<IActivation> pact):Ncells(number_of_cells){
        isactivation_relu=dynamic_cast<ReLU*>(pact.get())==nullptr;
        auto cellproto = Cell(pact);
        for(size_t i=0;i<number_of_cells;++i) _cells.push_back(cellproto);
    }
    size_t Layer::size(){
        return Ncells;
    }

    arma::vec Layer::operator()(const arma::vec& x,const arma::mat& W) const{
        arma::vec y(_cells.size());          
        arma::vec t = (W* extendvector(x));
        int i=0;
        for(auto cell:_cells){
            y(i)=cell(t(i));
            ++i;
        }

        return y;
    }

    arma::vec  Layer::forward(const arma::vec& x, const arma::mat& W,const arma::vec* dummy){
        inputs = x;
        arma::vec t = (W* extendvector(x));
      
        int i=0;
        std::vector<double> gf,f;
        for(auto cell:_cells){
            cell.compute(t(i++));
            double out,dout;
            std::tie(out,dout) = cell.getData();
            f.push_back(out);
            gf.push_back(dout);                        
        }

        outputs = arma::vec(f);
        doutputs = arma::vec(gf);       
        outputs_1 = extendvector(outputs);
        
        return outputs;
    }

    const arma::vec& Layer::getOutputs(bool extended){
        if(!extended){
            return outputs;
        }
        else{
            return outputs_1;
        }
        
    }

    const arma::vec& Layer::getInputs(){
        return inputs;
    }

    arma::vec Layer::derivatives(){        
        return doutputs;
    }

    bool Layer::isActivationReLU() const{
        return isactivation_relu;
    }
}}