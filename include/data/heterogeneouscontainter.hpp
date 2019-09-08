#ifndef HETEROGENEOUS_CONTAINER_H
#define HETEROGENEOUS_CONTAINER_H
#include <variant>
#include <type_traits>
#include <utility>
namespace AIX{namespace Data{
    template<typename  ... T>
    class HeterogeneousVector{
        std::vector<std::variant<T ...>> _container;
        public:
        template<typename A>
        void push(A&& x){
            _container.push_back(std::forward<A>(x));
        };
    };
}}

#endif