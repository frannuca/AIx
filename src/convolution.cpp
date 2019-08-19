#include "cnn/convolution.hpp"
#include <iostream>
#include <future>
#include <chrono>
#include <tuple>
#include <iostream>
#include <future>
#include <chrono>
#include <algorithm>
#include <memory>

namespace AIX{namespace CNN
{
    using namespace Concurrency;
    
        std::function<arma::mat(const arma::mat&)> 
            get_convolute(const arma::mat& a,
                          size_t stridex, size_t stridey,
                          Scheduler<void>& pScheduler){

        int Ra = a.n_rows;
        int Ca = a.n_cols;

        return [Ra,Ca,&pScheduler,stridex,stridey,a](const arma::mat& b){

        
        int Rb = b.n_rows;
        int Cb = b.n_cols;                               
        int Nx = (Ca-Cb)/stridex+1;
        int Ny = (Ra-Rb)/stridey+1;

        arma::mat rc(Ny,Nx);                

        auto assignvalue = [&rc,&b](int ni, int nj, decltype(a.submat(0,0,1,1)) tsub) {           
            rc(ni,nj) = arma::accu(tsub % b);
            };

        
            std::vector<std::future<void>> v;
            for(int i=0;i<Ny;i++){                        
                for(int j=0;j<Nx;j++){
                    auto tsub = a.submat(i*stridey,j*stridex,i*stridey+Rb-1,j*stridex+Cb-1);  
                    int ix = i;
                    int jx = j;
                    v.push_back(std::move(pScheduler.push([ix,jx,&assignvalue,tsub](){assignvalue(ix,jx,tsub);})));
                }
            }        
            for(auto& f: v) f.get();
        
        return rc;
    };
    }
}} // namespace cnn
