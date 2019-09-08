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

// the variant to visit
using var_t = std::variant<int, long, double, std::string>;
 
// helper type for the visitor #3
template<class T> struct always_false : std::false_type {};
 
// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
 
int main() {

    AIX::Data::HeterogeneousVector<double,int,bool> v;
    double a=1.0;
    bool b = false;
    int c = 2;
    v.push(a);
    v.push(b);
    v.push(c);

    AIX::Data::Series<int,double> s ({std::make_pair(1,1.0),std::make_pair(2,2.0),std::make_pair(3,3.0),std::make_pair(4,4.5)});
    AIX::Data::Series<int,double> s2 ({500,200,300,400,100},{1500.0,1200.0,1300.0,1400.0,1100.0});
    s2.sort();
    for(auto& p:s2){
        auto a = s2[p];
        std::cout<<p<<"->"<<s2[p]<<std::endl;
    }    
    
    
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