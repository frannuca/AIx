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
//#include "../concepts.hpp"
#include "series_iterator.hpp"

namespace AIX{
    namespace Data{
        using namespace std;

        /*!
         * Implements a dictionary type collection designed mainly for time series manipulation.
         * class Series offers user defined key sorting, first class function operations (map_values, map_keys),
         * arithmetic operators
         * @tparam K Key or Index type
         * @tparam T Value type
         */
        template<class K,class T>
    class Series  {
            //BOOST_CONCEPT_ASSERT((AIX::Concepts::HasLessThanOp<K>));
            protected:
            mutable map<K,T>  _data;
            mutable vector<K> _index;
            bool isSorted=false;
            function<bool(const K&, const K&)> _fcomp=less<K>();

            void order();
            void orderWith(decltype(_fcomp) fcomp);

            void throwForExistingKey(const K& k);

            int locate(const K& k);
            size_t updateIndex(const K& k);
           
            static Series<K,T> applyBinaryOp(const Series<K,T>& a, const Series<K,T>& b, function<T(const T&, const T&)> ops);

            static Series<K,T> applyBinaryOp(const Series<K,T>& a, const T& l, function<T(const T&, const T&)> ops);

            static Series<K,T> applyUnaryOp(const Series<K,T>& a, function<T(const T&)> ops);

            public:

            template<class Kx,class Tx>
            friend class const_iterator;

            using const_iterator_t = series_const_iterator<K,T>;

            Series()=default;
            
            Series(const Series<K,T>& that):_index(that._index), _data(that._data){}

            Series(Series<K,T>&& that): _index(move(that._index)),
                                        _data(std::move(that._data))
            {}
            size_t size() const {return _index.size();}
            Series<K,T>& operator=(const Series<K,T>& that);

            void clear();

            Series<K,T>& operator=(Series<K,T>&& that);
            
            void fill_missing(const set<K>& xaxis);

            void align_index(const set<K>& xaxis);

            bool operator==(const Series<K,T>& that) const ;

            bool operator !=(const Series<K,T>& that) const;
            
            const vector<K> Keys() const {return _index;}
          
            Series<K,T>& add_item(const K& k, const T& v);

            Series<K,T>& add_item(const K& k,  T&& v);

            Series<K,T>& add_item(const pair<K,T>& x);

            bool hasKey(const K& k) const;

            Series<K,T>& add_items(const vector<pair<K,T> >& x);
        
            Series<K,T>& add_items(const vector<K>& keys, const vector<T>& v);
            
            void join(const Series<K,T>& series,bool overridevalues);

            bool remove_item(const K& k);
            
            const vector<K>& sortbykey();

            const vector<K>& sortbykeyWith(function<bool(const K&,const K&)> fcomp);

            T& operator[](const K& k);
            T operator[](const K& k) const;
            const_iterator_t begin(){return const_iterator_t(&_index[0]);}
            const_iterator_t end(){return const_iterator_t(&_index[0] + _index.size());}

            const_iterator_t begin() const {return const_iterator_t(&_index[0]);}
            const_iterator_t end() const {return const_iterator_t(&_index[0] + _index.size());}


            Series<K,T> operator+(const Series<K,T>& that) const{
                return applyBinaryOp(*this, that, [](const T &a, const T &b) { return a + b; });
            }

            Series<K,T> operator-(const Series<K,T>& that) const{
                return applyBinaryOp(*this, that, [](const T &a, const T &b) { return a - b; });
            }

            Series<K,T> operator*(const Series<K,T>& that) const{
                return applyBinaryOp(*this, that, [](const T &a, const T &b) { return a * b; });
            }

            Series<K,T> operator*(const T& l) const{
                return applyBinaryOp(*this, l, [](const T &a, const T &b) { return a * b; });
            }

            Series<K,T> operator/(const Series<K,T>& that) const{
                return applyBinaryOp(*this, that, [](const T &a, const T &b) { return a / b; });
            }

            Series<K,T> operator/(const T& l) const{
                return applyBinaryOp(*this, l, [](const T &a, const T &b) { return a / b; });
            }

            Series<K,T> operator+(const T& l) const{
                return applyBinaryOp(*this, l, [](const T &a, const T &b) { return a + b; });
            }

            Series<K,T> operator-() const{
                return applyUnaryOp(*this, [](const T &a) { return -a; });
            }

            Series<K,T> inv() const{
                return applyUnaryOp(*this, [](const T &a) { return 1.0 / a; });
            }

            template<class S>
            Series<K,S> map_values(function<S(const T&)> op){

                Series<K,S> newseries;
                for(auto& k:*this){
                    newseries.add_item(k,op(this->operator[](k)));
                }

                return newseries;
            }

            template<class S>
            Series<K,T> map_keys(function<S(const K&)> op){
                Series<S,T> newseries;
                for(auto& k:*this){
                    newseries.add_item(op(k),this->operator[](k));
                }

                return newseries;
            }


            template<class Kx, class Tx>
            friend Series<Kx,Tx> operator+(const Tx& l, const Series<Kx,Tx>& x);

            template<class Kx, class Tx>
            friend Series<Kx,Tx> operator*(const Tx& l, const Series<Kx,Tx>& x);

            template<class Kx, class Tx>
            friend Series<Kx,Tx> operator/(const Tx& l, const Series<Kx,Tx>& x);

            template<class Kx,class Tx>
            friend std::ostream& operator<<(std::ostream& , const Series<Kx,Tx>& );
        };



    }
}

#include "series.tcc"
#endif