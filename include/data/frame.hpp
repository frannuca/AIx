#ifndef FRAME_H
#define FRAME_H
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <map>
#include <set>

namespace AIX{
    namespace Data{
    using namespace std;
    using namespace boost::multi_index;

    
    template<typename K, typename C>
    class Frame{
        
        
        set<K> _index;
        
        public:
        Frame(){};
        
        template<typename T>
        void add_column(const C& id, const map<K,T>& x){
            
        }

        template<typename T>
        const T& get(const C& column,const K& key) const{
            
        }

    };

}}
#endif