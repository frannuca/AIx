#ifndef FRAME_H
#define FRAME_H
#include <map>
#include <any>
#include <utility>
#include <functional>

namespace AIX{
    namespace Data{

    template<typename K, typename C, class Comparator=std::less<>>
    class Frame{
        std::map<C,std::map<K,std::any>,Comparator> _columns;        
        
        public:

        template<typename T>
        void add_column(const std::string& columnname, const std::map<K,T>& x);

        template<typename T>
        std::map<K,T>& operator[](const C& column);

    };

    
    template<typename K, typename C,typename Comparator>
    template<typename T>
    void Frame<K,C,Comparator>::add_column(const std::string& columnname, const std::map<K,T>& x){
        _columns[columnname]=x;
    }  

    template<typename K, typename C,typename Comparator>
    template<typename T>
    std::map<K,T>& Frame<K,C,Comparator>::operator[](const C& column){
        return _columns[column];
    }

}}
#endif