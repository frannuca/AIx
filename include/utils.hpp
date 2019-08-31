#ifndef UTILS_H
#define UTILS_H
#include <armadillo>

namespace AIX{

    arma::vec extendvector(const arma::vec& x, const double& v=1);
    
    arma::subview<double> reduceLastColumn(const arma::mat& m);
    arma::subview<double> reduceLastRow(const arma::mat& m);


}
#endif