#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include <utility>
#include "data/frame.hpp"
#include <iterator>
#include <random>

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

struct MyVisitor
{
    template<class T>
    void operator()(T& _in){_in += _in;}
};

template<class... T>
struct VariantContainer
{
    template<class V>
    void visit(V&& visitor)
    {
        for (auto& object : objects)
        {
            std::visit(visitor, object);
        }
    }
    using value_type = std::variant<T...>;
    std::vector<value_type> objects;
};

struct heterogeneous_container{
private:
    template<class T>
    static std::unordered_map<const heterogeneous_container*, std::vector<T>> items;
public:
    heterogeneous_container(){}
    heterogeneous_container(const heterogeneous_container& that){
        *this = that;
    }

    heterogeneous_container& operator=(const heterogeneous_container& that){
        clear();
        copy_functions = that.copy_functions;
        clear_functions = that.clear_functions;

        for(auto& fcopy:that.copy_functions){
            fcopy(that,*this);
        }

        return *this;
    };

    ~heterogeneous_container(){
        clear();
    }

    std::vector<std::function<void(heterogeneous_container&)>> clear_functions;
    std::vector<std::function<void(const heterogeneous_container&,heterogeneous_container&)> > copy_functions; 

    void clear(){
        for(auto& fdel : clear_functions) fdel(*this);
    }
    template<class T>
    void push_back(const T& _t)
    {
        // don't have it yet, so create functions for destroying
        if (items<T>.find(this) == std::end(items<T>))
        { 
            clear_functions.emplace_back(
                [](heterogeneous_container& _c){items<T>.erase(&_c);});

            copy_functions.emplace_back([](const heterogeneous_container& from, heterogeneous_container& to){
                items<T>[&to]=items<T>[&from];
            });
        }
        items<T>[this].push_back(_t);
    }
};

// storage for our static members
template<class T>
std::unordered_map<const heterogeneous_container*, std::vector<T>> heterogeneous_container::items;


template<class...>
struct type_list{};

template<class ... TYPES>
struct visitor_base{
    using types = type_list<TYPES ...>;
};


struct my_visitor : visitor_base<int, double>
{
    template<class T>
    void operator()(T& _i) 
    {
        _i+=_i;
    }    
};

template<class T>
void visit(T&& visitor)
{
    visit_impl(visitor, typename std::decay_t<T>::types{});
};

// template<class T, class U>
// void visit_impl_help(T& visitor)
// {
//     for (auto&& element : items<U>[this])
//     {
//         visitor(element);
//     }
// };


// template<class T, template<class...> class TLIST, class... TYPES>
// void visit_impl(T&& visitor, TLIST<TYPES...>)
// {
//    (..., visit_impl_help<std::decay_t<T>, TYPES>(visitor));
// };



int main()
{   
    heterogeneous_container hcont;
    hcont.push_back(std::string("hello"));
    hcont.push_back(6.0);
    hcont.push_back(true);
    hcont.push_back(10);
    auto lambdaPrintVisitor = [](auto&& _in){std::cout << _in << " ";};
    VariantContainer<int, double, std::string> variantCollection;
    variantCollection.objects.emplace_back(1);
    variantCollection.objects.emplace_back(2.2);
    variantCollection.objects.emplace_back("foo");
    
    // print them
    variantCollection.visit(lambdaPrintVisitor);
    std::cout << std::endl;
    
    // double them
    variantCollection.visit(MyVisitor{});
    
    // print again
    variantCollection.visit(lambdaPrintVisitor);
    std::cout << std::endl;

}