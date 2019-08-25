#include "mlp/softmax.hpp"
#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include <math.h>
#include <memory>

int c_exp = 1.0;
namespace AIX{
    namespace MLP{

        Softmax::Softmax(size_t number_of_classes_):Layer(number_of_classes_,std::shared_ptr<AIX::Exponential>(new AIX::Exponential(c_exp))){
            isactivation_relu=false;                        
        }
        
        arma::vec Softmax::forward(const arma::vec& x, const arma::mat& W,const arma::vec* yout){
             auto& wn = W.submat(0,0,arma::SizeMat(W.n_rows,x.size()));
                
        auto a1 = wn * x;
        auto& b1 = W.col(x.size());
        auto c = a1 + b1;
        
        inputs = c;
        auto& s = inputs;

        int i=0;
        int istatus=-1;
        std::vector<double> f;
        double total =0.0;
        for(auto cell:_cells){
            if(yout != nullptr){
                if((*yout)(i)==1.0){
                    istatus = i;
                }
            }
            cell.compute((*s)(i++));
            double out,dout;
            std::tie(out,dout) = cell.getData();
            total += out;
            f.push_back(out);            
        }

       

        
        if(total != total){
            std::cout<<W<<std::endl;
            std::cout<<x<<std::endl;
            std::cout<<*yout<<std::endl;
        }
        
        for(int i=0;i<f.size();++i){
            f[i] = f[i]/total;
        }
        
        std::vector<double> gf;
        for(size_t i = 0; i<f.size() && istatus >=0;++i){
            
            if(istatus == i){
                gf.push_back(c_exp*f[istatus]*(1.0-f[istatus]));                
            }
            else{
                gf.push_back(-c_exp*f[istatus]*f[i]);
            }
        }
        
        outputs = arma::vec(f);
        doutputs = arma::vec(gf);
        f.push_back(1.0);
        outputs_1 = arma::vec(f);
        
        return outputs.get();
        }              
    }
}