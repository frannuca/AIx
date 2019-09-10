#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include <utility>
#include "data/heterogeneouscontainter.hpp"
#include "data/series.hpp"
#include <iterator>
#include <random>

int main() {
    using namespace AIX;
    using namespace AIX::Data;

    std::cout<<"*************************************"<<std::endl;
    std::cout<<"*        Series Tests                *"<<std::endl;
    std::cout<<"*************************************"<<std::endl;


    std::vector<int> axis(1000,0);
    std::vector<double> values1(1000,0.0);
    std::vector<Axis<int,double>> axispairs(500,Axis(0,0.0));
    
    std::random_device rd;
    std::mt19937 g(rd());

    std::generate(axis.begin(),axis.end(),[n=0]() mutable{return n++;});
    std::shuffle(axis.begin(),axis.end(),g);

    std::generate(values1.begin(),values1.end(),[](){return (double)std::rand()/(double)RAND_MAX;});

    std::generate(axispairs.begin(),axispairs.end(),[n=0]() mutable {return Axis(n++, (double)std::rand()/(double)RAND_MAX);});
    std::shuffle(axispairs.begin(),axispairs.end(),g);

    std::cout<<"Checking ctor Series(keys, values)"<<std::endl;
    Series<int,double> series_1(axis,values1);

    std::cout<<"Checking ctor Series(axis)"<<std::endl;
    Series<int,double> series_2(axispairs);
    
    std::cout<<"Sorting ascending (default) and checking order"<<std::endl;
    series_1.sort();
    auto series1keys = series_1.Keys();
    for(size_t i=0;i<series1keys.size()-1;++i){ assert(series1keys[i]<series1keys[i+1]);};
    
    std::cout<<std::endl;
    std::cout<<"Sorting descending (default) and checking order"<<std::endl;
    series_2.sort(false);
    auto series2keys = series_2.Keys();
    for(size_t i=0;i<series2keys.size()-1;++i){ assert(series2keys[i]>series2keys[i+1]);};

    std::cout<<std::endl;
    std::cout<<"Summing series"<<std::endl;
    Series<int,double> series_1p2 = series_1+series_2;
    for(auto& k : series_1p2.Keys()){
        double d = series_1p2[k] - series_1[k] - series_2[k];        
        assert(std::abs(d)<1e-10);
    }
    
    std::cout<<std::endl;
    std::cout<<"Chekcing unitary minus"<<std::endl;
    auto series_minus = -series_1;
    for(auto& k : series_minus.Keys()){
        
        assert(std::abs(series_minus[k] + series_1[k])<1e-10);      
    }
    

    std::cout<<std::endl;
    std::cout<<"Subtracting series"<<std::endl;
    auto series_1m2 = series_1 - series_2;
    for(auto& k : series_1m2.Keys()){
        double d = series_1m2[k] - series_1[k] + series_2[k];
        assert(std::abs(d)<1e-10);      
    }
    
    std::cout<<"operator[] with assign"<<std::endl;
    series_1[257]=33.3;
    assert(series_1[257]==33.3);
    std::cout<<"OK";
}


/**
 * std::vector<var_t> vec = {10, 15l, 1.5, "hello"};
    for(auto& v: vec) {
 
        // 1. void visitor, only called for side-effects (here, for I/O)
        std::visit([](auto&& arg){std::cout << arg;}, v);
 
        // 2. value-returning visitor, demonstrates the idiom of returning another variant
        var_t w = std::visit([](auto&& arg) -> var_t {return arg + arg;}, v);
 
        // 3. type-matching visitor: a lambda that handles each type differently
        std::cout << ". After doubling, variant holds ";
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>)
                std::cout << "int with value " << arg << '\n';
            else if constexpr (std::is_same_v<T, long>)
                std::cout << "long with value " << arg << '\n';
            else if constexpr (std::is_same_v<T, double>)
                std::cout << "double with value " << arg << '\n';
            else if constexpr (std::is_same_v<T, std::string>)
                std::cout << "std::string with value " << std::quoted(arg) << '\n';
            else 
                static_assert(always_false<T>::value, "non-exhaustive visitor!");
        }, w);
    }
 
    for (auto& v: vec) {
        // 4. another type-matching visitor: a class with 3 overloaded operator()'s
        std::visit(overloaded {
            [](auto arg) { std::cout << arg << ' '; },
            [](double arg) { std::cout << std::fixed << arg << ' '; },
            [](const std::string& arg) { std::cout << std::quoted(arg) << ' '; },
        }, v);
    }
 * */