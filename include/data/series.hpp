#ifndef SERIES_H
#define SERIES_H

#include <map>
#include <vector>
#include <algorithm>
#include <exception>
#include <utility>
#include <functional>
#include <optional>
#include <memory>
#include <iterator>
#include <assert.h>

namespace AIX{namespace Data{

    template<class K, class V>
    class Series_Iterator;

    template<class K, class V>
    class Series_rev_Iterator;

    

    template<typename K, typename V>
    class Series{
        public:
        using Container = std::vector<std::pair<K,V>>;   
        using const_iterator = Series_Iterator<K,V>;
        using const_reverse_iterator = Series_rev_Iterator<K,V>;

        Series(const std::vector<K>& keys,const std::vector<V>& values);                        
        Series(std::vector<std::pair<K,V>>&& keyvalues);

        Series(const Series<K,V>& that);
        Series(Series<K,V>&& that);

        Series<K,V>& operator=(const Series<K,V>& that);
        Series<K,V>& operator=(Series<K,V>&& that);

        void sort(bool descendentorder=true);
        V& operator[](const K& i);
        V operator[](const K& i) const;
        std::vector<K> Keys() const;
        
        const_iterator begin(){return  Series_Iterator<K,V>(this,0);}
        const_iterator end()  {return  Series_Iterator<K,V>(this,_data.size());}


        const_reverse_iterator rbegin() const {return  Series_Iterator<K,V>(this,_data.size());}
        const_reverse_iterator rend()  const {return  Series_Iterator<K,V>(this,0);}

        std::size_t size(){return _data.size();}
        
        template<class A, class B>
        friend  Series<A,B> operator+(const Series<A,B>& a, const Series<A,B>& b);

        template<class A, class B> 
        friend class Series_Iterator;

        protected:        
        Container _data; 
        std::optional<bool> sortedDescendent;   

    };

template<class K, class V>
class Series_Iterator{
        public:            
            using value_type = K;
            using pointer    = K*;
            using reference  = K&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;
            
            Series_Iterator():                    v(nullptr), i(0) {}   
            Series_Iterator(Series<K,V>* v, int i): v(v),       i(i) {}
            Series_Iterator(const Series_Iterator<K,V>& that):i(that.i),v(that.v){}
  

            reference operator*()                 {return v->_data[i].first;}            
            const reference operator*() const     {return v->_data[i].first;}
            
            Series_Iterator<K,V>& operator=(const Series_Iterator<K,V>& that){i = that.i;v = that.v;return *this;}            

                    
        
            Series_Iterator<K,V>& operator++()        {++i;return *this;}
            Series_Iterator<K,V>& operator--()        {--i;return *this;}
            
            Series_Iterator<K,V>& operator+(int n)    {i+=n;return *this;}
            Series_Iterator<K,V>& operator-(int n)    {i-=n;return *this;}
            
            Series_Iterator<K,V>& operator+=(int n)    {i+=n;return *this;}
            Series_Iterator<K,V>& operator-=(int n)    {i-=n;return *this;}
            
            reference operator[](const size_t& n)    {return v[n].first;}

            // Note: comparing iterator from different containers
            //       is undefined behavior so we don't need to check
            //       if they are the same container.
            virtual bool operator<(Series_Iterator<K,V> const& r)  const {return v->_data[i].first <  r.v->_data[r.i].first;}
            virtual bool operator<=(Series_Iterator<K,V> const& r) const {return v->_data[i].first <= r.v->_data[r.i].first;}
            virtual bool operator>(Series_Iterator<K,V> const& r)  const {return v->_data[i].first >  r.v->_data[r.i].first;}
            virtual bool operator>=(Series_Iterator<K,V> const& r) const {return v->_data[i].first >= r.v->_data[r.i].first;}
            bool operator!=(const Series_Iterator<K,V> &r) const {return v->_data[i].first != r.v->_data[r.i].first;}
            bool operator==(const Series_Iterator<K,V> &r) const {return v->_data[i].first == r.v->_data[r.i].first;}

            template<class A, class B>
            friend Series_Iterator<A,B>& operator+(int n,Series_Iterator<A,V>&);

            template<class A, class B>
            friend Series_Iterator<A,B>& operator-(int n,Series_Iterator<A,V>&);

            difference_type operator-(const Series_Iterator<K,V>& that){
                return this->i-that.i;        
            }

        protected:
            Series<K,V>* v;
            int        i;
        };

    template<class K, class V>
    Series_Iterator<K,V>& operator+(int n,Series_Iterator<K,V>& that){
        that.i += n;
        return *that;
    }

    template<class K, class V>
    Series_Iterator<K,V>& operator-(int n,Series_Iterator<K,V>& that){
        that.i -= n;
        return *that;
    }
   
   
   
    template<class K, class V>
    Series<K,V>::Series(const std::vector<K>& keys, const std::vector<V>& values){
        assert(keys.size() == values.size());
        
        std::transform(keys.begin(),keys.end(),values.begin(),std::back_inserter(_data),
                            [](const K& a,const V& b){return std::move(std::pair<K,V>(a,b));});           
    }

    template<class K, class V>
    Series<K,V>::Series(Series<K,V>::Container&& keyvalues):_data(std::forward<Series<K,V>::Container>(keyvalues)){}
   

     template<class K, class V>
    Series<K,V>::Series(const Series<K,V>& that){
        _data = that._data;
    }
    
    template<class K, class V>
    Series<K,V>::Series(Series<K,V>&& that){
            _data = std::move(that._data);
    }

    template<class K, class V>
    Series<K,V>& Series<K,V>::operator=(const Series<K,V>& that){
        _data = that._data;
        return *this;
    }

    template<class K, class V>
    Series<K,V>& Series<K,V>::operator=(Series<K,V>&& that){
        _data = std::move(that._data);
        return *this;
    }

    template<class K, class V>
    V& Series<K,V>::operator[](const K& i){
       
       auto ilow = std::lower_bound(this->begin(),this->end(),i);
       if(ilow == this->end()){
           throw "Not found";
       }
       int d = std::distance(this->begin(),ilow);
       return _data[d].second;
    }

    template<class K, class V>
    V Series<K,V>::operator[](const K& i) const{
       return _data[i].second;
    }

    template<class K, class V>
    std::vector<K> Series<K,V>::Keys() const{
        std::vector<K> keys;
        std::transform(_data.begin(),_data.end(),std::back_inserter(keys),[](auto& a){return a.first();});
        return keys;
    }

    template<class K, class V>
    void Series<K,V>::sort(bool descendentorder){
        if(sortedDescendent && *sortedDescendent){
            return;
        }

        if(descendentorder){
            std::sort(_data.begin(),_data.end(),[](auto& a, auto& b){return a<b;});
        }
        else{
            std::sort(_data.begin(),_data.end(),[](auto& a, auto& b){return a>b;});
        }
        sortedDescendent= descendentorder;
    }

    template<class K, class V>
    Series<K,V> operator+(const Series<K,V>& a, const Series<K,V>& b){
        std::vector<std::pair<K,V>> sum;
        
    }
}
}
#endif