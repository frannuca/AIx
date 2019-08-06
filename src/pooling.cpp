#include "pooling.hpp"

namespace cnn{
    std::function<arma::mat(int,int)> get_pooling(const arma::mat& imagex,std::shared_ptr<Scheduler<void>> pScheduler){
        
        using namespace concurrency;
            

        int Ra = imagex.n_rows;
        int Ca = imagex.n_cols;

        return [=](int nrows,int ncols){

        
        int Rb = nrows;
        int Cb = ncols;                               
        int Nx = (Ca-Cb)+1;
        int Ny = (Ra-Rb)+1;

        arma::mat rc(Ny,Nx);                

        auto assignvalue = [&rc](int ni, int nj, decltype(imagex.submat(0,0,1,1)) tsub) {                        
            rc(ni,nj) = tsub.max();            
            };

        
        if(pScheduler){
            std::vector<std::future<void>> v;
            for(int i=0;i<Ny;i++){                        
                for(int j=0;j<Nx;j++){
                    auto tsub = imagex.submat(i,j,i+Rb-1,j+Cb-1);                 
                    int ix = i;
                    int jx = j;
                    v.push_back(std::move(pScheduler->push([ix,jx,&assignvalue,tsub](){assignvalue(ix,jx,tsub);})));
                }
            }        
            for(auto& f: v) f.get();
        }
        else{
            for(int i=0;i<Ny;i++){                        
                for(int j=0;j<Nx;j++){
                    auto tsub = imagex.submat(i,j,i+Rb-1,j+Cb-1);                 
                    assignvalue(i,j,tsub);
                }      
            }  
        }  
        return rc;
    };
}
}
