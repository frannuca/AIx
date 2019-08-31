#include "utils.hpp"
namespace AIX{
    arma::vec extendvector(const arma::vec& x,const double& v){
        
        arma::vec xx(x.size()+1);
        xx(xx.size()-1)=v;
        int i=0;
        for(auto& s:x)xx(i++)=s;
        return xx;
    }

    arma::subview<double> reduceLastColumn(const arma::mat& m){
        return m.submat(0,0,arma::SizeMat(m.n_rows,m.n_cols-1));
    }
    arma::subview<double> reduceLastRow(const arma::mat& m){
        return m.submat(0,0,arma::SizeMat(m.n_rows-1,m.n_cols));
    }
}