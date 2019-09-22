#ifndef SERIES_H
#define SERIES_H
#include <vector>
#include <memory>
#include <utility>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <utility>
#include <optional>
#include <exception>
#include <sstream>
#include <type_traits>
#include "../utils.hpp"

namespace AIX{
    namespace Data{
        using namespace std;


        template<class K,class T>
        class Series{
            protected:
            mutable map<K,T>  _data;
            vector<K> _index;            
            bool isSorted=false;
            

            void order(){
                sort(_index.begin(),_index.end(),std::less<K>());
                isSorted=true;
                }

            void throwForExistingKey(const K& k){
              if(_data.find(k)!=_data.end()){
                  ostringstream msg;
                  msg<<"The key"<<k<<" is already part of the Series index";
                  throw invalid_argument(msg.str());
              }  
            }
            size_t updateIndex(const K& k){
                int n=-1;
                if(isSorted){
                    typename vector<K>::iterator nlow, nhigh;
                    tie(nlow,nhigh)=equal_range(_index.begin(),_index.end(),k);
                    if(nlow==nhigh){
                        return distance(_index.begin(),nlow); 
                    }
                    n = distance(_index.begin(),nlow);
                }
                else{
                    n = _index.size();
                }
                
                _index.insert(_index.begin()+n,k);
                return n;
            }
           
           static Series<K,T> applybinaryop(const Series<K,T>& a, const Series<K,T>& b,function<T(const T&,const T&)> ops){
                set<K> keys = AIX::intersection(a.Keys(),b.Keys());
                set<K> missing = AIX::symdifference(a.Keys(),b.Keys());

                Series<K,T> sumseries;
                for(auto& k:keys){
                    sumseries.add_item(k,ops(a[k],b[k]));
                }

                for(auto& k:missing){
                    sumseries.add_item(k,Missing::get_missing<T>(0));
                }

                return sumseries;
           }

           static Series<K,T> applybinaryop(const Series<K,T>& a, const T& l,function<T(const T&,const T&)> ops){
                vector<K> keys =a.Keys();
            

                Series<K,T> sumseries;
                for(auto& k:keys){
                    sumseries.add_item(k,ops(a[k],l));
                }

                return sumseries;
           }

           
            public:
            
            class const_iterator{
                public:
                    typedef const_iterator self_type;
                    typedef K value_type;
                    typedef K& reference;
                    typedef K* pointer;
                    typedef ptrdiff_t difference_type;
                    typedef std::forward_iterator_tag iterator_category;

                    typedef const K& const_reference;

                    const_iterator(pointer ptr) : ptr_(ptr) { }
                    const_iterator& operator=(const const_iterator& that){
                        this->ptr_ = that.ptr_;
                        return *this;
                    }

                    self_type operator++() { self_type i = *this; ptr_++; return i; }
                    self_type operator++(int junk) { ptr_++; return *this; }
                    
                    const_reference operator*() { return *ptr_; }
                    const pointer operator->() { return ptr_; }
                    bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
                    bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
                private:
                    pointer ptr_;
            };

            Series()=default;
            
            Series(const Series<K,T>& that):_index(that._index), _data(that._data){}

            Series(Series<K,T>&& that): _index(move(that._index)),
                                        _data(std::move(that._data))
            {}

            Series<K,T>& operator=(const Series<K,T>& that){
                this->_data = that._data;
                this->_index = that._index;
                return *this;
            }

            Series<K,T>& operator=(Series<K,T>&& that){
                this->_data = move(that._data);
                this->_index = move(that._index);
                return *this;
            }

            const vector<K> Keys() const {return _index;}
          
            Series<K,T>& add_item(const K& k, const T& v){
                throwForExistingKey(k);             
                _data[k]=v;
                updateIndex(k);
                
                return *this;
            }
            
            Series<K,T>& add_item(const pair<K,T>& x){
                throwForExistingKey(x.first);
                _data.insert(x);
                updateIndex(x.first);
                return *this;
            }

            Series<K,T>& add_items(const vector<pair<K,T> >& x){
                for(const pair<K,T>& kv: x){
                    add_item(kv);
                }
                
                return *this;
            }
        
            Series<K,T>& add_items(const vector<K>& keys, const vector<T>& v){
                assert(keys.size()==v.size());
                for(size_t i=0;i<keys.size();++i) 
                {
                    add_item(keys[i],v[i]);
                }
                return *this;
            }
            
            
            const vector<K>& sortbykey(){
                if(!isSorted)
                    order();

                return _index;
            }

            T& operator[](const K& k){
                return _data[k];
            }
            T operator[](const K& k) const{
                T a = _data[k];
                return a;
            }
            const_iterator begin(){return const_iterator(&_index[0]);}
            const_iterator end(){return const_iterator(&_index[0] + _index.size());}


            Series<K,T> operator+(const Series<K,T>& that) const{
                return applybinaryop(*this,that,[](const T& a, const T& b){return a + b;});
            }

            Series<K,T> operator-(const Series<K,T>& that) const{
                return applybinaryop(*this,that,[](const T& a, const T& b){return a - b;});
            }

            Series<K,T> operator*(const Series<K,T>& that) const{
                return applybinaryop(*this,that,[](const T& a, const T& b){return a * b;});
            }

            Series<K,T> operator*(const T& l) const{
                return applybinaryop(*this,l,[](const T& a, const T& b){return a * b;});
            }

            Series<K,T> operator/(const Series<K,T>& that) const{
                return applybinaryop(*this,that,[](const T& a, const T& b){return a / b;});
            }

            Series<K,T> operator/(const T& l) const{
                return applybinaryop(*this,l,[](const T& a, const T& b){return a / b;});
            }

            Series<K,T> operator+(const T& l) const{
                return applybinaryop(*this,l,[](const T& a, const T& b){return a + b;});
            }

            template<class Kx, class Tx>
            friend Series<Kx,Tx> operator+(const Tx& l, const Series<Kx,Tx>& x);

            template<class Kx, class Tx>
            friend Series<Kx,Tx> operator*(const Tx& l, const Series<Kx,Tx>& x);

            template<class Kx, class Tx>
            friend Series<Kx,Tx> operator/(const Tx& l, const Series<Kx,Tx>& x);

        };

        template<class K, class T>
        Series<K,T> operator+(const T& l, const Series<K,T>& series){
            return series + l;
        }

        template<class K, class T>
        Series<K,T> operator*(const T& l, const Series<K,T>& series){
            return series * l;
        }

        template<class K, class T>
        Series<K,T> operator/(const T& l, const Series<K,T>& series){
            return series * (1.0/l);
        }

    }
}
#endif