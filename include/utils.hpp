#ifndef UTILS_H
#define UTILS_H
#include <armadillo>
#include <set>
#include <algorithm>
#include <type_traits>
#include <limits>
#include <utility>

namespace AIX{

    arma::vec extendvector(const arma::vec& x, const double& v=1);
    
    arma::subview<double> reduceLastColumn(const arma::mat& m);
    arma::subview<double> reduceLastRow(const arma::mat& m);

    template<class Container >
    std::set<typename Container::value_type> intersection( const Container& a,  const Container& b){
        std::set<typename Container::value_type> r;
        std::set_intersection(a.begin(),a.end(),b.begin(),b.end(),std::inserter(r,r.begin()));
        return r;
    };

    template<class Container >
    std::set<typename Container::value_type> symdifference( const Container& a,  const Container& b){
        std::set<typename Container::value_type> r;
        std::set_symmetric_difference(a.begin(),a.end(),b.begin(),b.end(),std::inserter(r,r.begin()));
        return r;
    };

    struct Missing{
       
        template<typename C>
        static C get_missing(decltype(std::numeric_limits<C>::quiet_NaN())* p){return std::numeric_limits<C>::quiet_NaN();}

        template<typename C>
        static C get_missing(...){C a; return a;}
        
    };

    
}
#endif