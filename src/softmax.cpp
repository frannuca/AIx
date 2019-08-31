#include "mlp/softmax.hpp"
#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include <math.h>
#include <memory>
#include <iostream>
#include "utils.hpp"

int c_exp = 1.0;
namespace{
bool checknan(const arma::mat& a){
            double x = arma::accu(a);
            
            return x!=x;
};

bool checknan(const arma::vec& a){
            double x = arma::sum(a);
            return x!=x;
};

bool checknan(const std::vector<double>& gf){
    double x = std::accumulate(gf.begin(),gf.end(),0.0);
    return x != x;
}
}

namespace AIX{
    namespace MLP{

        Softmax::Softmax(size_t number_of_classes_):Layer(number_of_classes_,std::shared_ptr<AIX::Exponential>(new AIX::Exponential(c_exp))){
            isactivation_relu=false;                        
        }
        arma::vec Softmax::operator()(const arma::vec& x,const arma::mat& W) const{
        arma::vec xx = extendvector(x);              
        arma::vec o(_cells.size());
        arma::vec t = W * xx;
        t = t - arma::max(t);      
        
        int i=0;
        for(auto cell:_cells){
            o(i) = cell(t(i));            
            i++;      
        }
        
        return o/arma::sum(o);      
    }

        arma::vec Softmax::forward(const arma::vec& x, const arma::mat& W,const arma::vec* yout){
             auto& wn = W.submat(0,0,arma::SizeMat(W.n_rows,x.size()));

        arma::vec xx = extendvector(x);              
        
        inputs = W*xx;
        
        int i=0;        
        std::vector<double> f;
        double total =0.0;
        for(auto cell:_cells){

            cell.compute(inputs(i));
            double out,dout;
            std::tie(out,dout) = cell.getData();
            total += out;
            f.push_back(out);      
            i++;      
        }
        
        
        int nstate=-1;        
        for(int i=0;i<f.size();++i){
            f[i] = f[i]/total;
            if(yout && (*yout)(i)==1){
                nstate=i;
            }
        }
        if(nstate>=0){
            arma::vec gf(f.size(),arma::fill::zeros);
            double cum=0;
            for(int k=0;k<gf.size();++k){
                double a = c_exp*f[nstate]*(int(nstate==k)-f[k]);
                gf(k)= a;
            }

            
            //std::cout<<"gf(nstate)"<<gf(nstate)<<std::endl;  

            if(checknan(gf)){
                std::cout<<"x="<<x.t()<<std::endl;
                std::cout<<"W"<<std::endl<<W<<std::endl;
                std::string sss;
                std::cin>>sss;
            }    
            doutputs = gf;
        }

        
        outputs = arma::vec(f);
        
        f.push_back(1.0);
        outputs_1 = arma::vec(f);
        
        return outputs;
        }              
    }
}