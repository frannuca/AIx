#include "../include/convolution.hpp"
#include <iostream>
#include <future>
#include <chrono>
#include <tuple>
#include <iostream>
#include <future>
#include <chrono>
#include <algorithm>
#include <memory>

namespace cnn
{
    using namespace concurrency;
    
        std::function<arma::mat(const arma::mat&)> 
            get_convolute(const arma::mat& a,
                          size_t stridex, size_t stridey,
                          std::unique_ptr<Scheduler<void>> pScheduler){

        int Ra = a.n_rows;
        int Ca = a.n_cols;

        return [&](const arma::mat& b){

        
        int Rb = b.n_rows;
        int Cb = b.n_cols;                       

        arma::mat rc(Ra-Rb-stridey,Ca-Cb-stridex);
        std::vector<std::future<void>> z;
        

        auto assignvalue = [&rc,&b](int ni, int nj, decltype(a.submat(0,0,1,1)) tsub) {rc[ni,nj] = arma::accu(tsub % b);};
        int ni = 0, nj = 0;
        for(int i=0;i<Ra;i+=stridey,++ni){                        
            for(int j=0;j<Ca;j+=stridex,++nj){
                auto tsub = a.submat(i,j,i+Rb-1,j+Cb-1);
                pScheduler->push([ni,nj,&assignvalue,&tsub](){assignvalue(ni,nj,tsub);});
            }
        }
        pScheduler->waitForCompletion();
        return rc;
    };
    }
} // namespace cnn
