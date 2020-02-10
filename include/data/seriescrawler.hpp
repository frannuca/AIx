//
// Created by Fran on 02.10.19.
//

#ifndef GLOBAL_SERIESCRAWLER_HPP
#define GLOBAL_SERIESCRAWLER_HPP
#include <functional>
#include <map>
#include "series.hpp"
#include <set>
namespace AIX{namespace Data{
    using namespace std;

    /*!
     * Heterogenous container of series with recurrent metaprogramming functions to iterate over all
     * instanciated series types. Mainly all series stored in this class differ in the value type T, Series<K,T>,
     * sharing the same key K type.
     * @tparam K type of the index (must be comparable)
     * @tparam C type of the columns
     * @tparam Ts variadic type hosting the value type of the series.
     */
    template<typename K, typename C, class ... Ts>
    class SeriesCrawler{
    protected:
        using type = SeriesCrawler<K,C,Ts ...>;
        vector<function<void(const type*)> > _clear_functions;
        map<C,function<void(const type*,const C&)> > _delete_column_function;
        vector<function<void(const type& from, type& to)> >  _copy_functions;
        vector<function<void(type&& from, type& to)> >  _copy_functions_move;
        function<bool(const K&, const K&)> _fcomp = less<K>();

        template<class T>
        static map<const type*,map<C,Series<K,T> > > _items;
    public:

        SeriesCrawler(){}


        SeriesCrawler(SeriesCrawler<K,C,Ts...>&& that){
            *this = forward<SeriesCrawler<K,C,Ts...>>(that);
        }

        SeriesCrawler<K,C,Ts...>(const SeriesCrawler<K,C,Ts...>& that){
            *this = that;
        }

        SeriesCrawler<K,C,Ts...>& operator=(const SeriesCrawler<K,C,Ts...>& that){
            this->_copy_functions = that._copy_functions;
            this->_copy_functions_move = that._copy_functions_move;
            this->_delete_column_function = that._delete_column_function;
            this->_clear_functions = that._clear_functions;
            this->_fcomp = that._fcomp;
            for(auto& f: that._copy_functions) f(that,*this);
            return *this;
        }

        SeriesCrawler<K,C,Ts...>& operator=(SeriesCrawler<K,C,Ts...>&& that) noexcept{
            this->_copy_functions = move(that._copy_functions);
            this->_copy_functions_move = move(that._copy_functions_move);
            this->_delete_column_function = move(that._delete_column_function);
            this->_clear_functions = move(that._clear_functions);
            this->_fcomp = that._fcomp;
            for(auto& f: this->_copy_functions_move) f(move(that),*this);
            that.clear();
            return *this;
        };
        virtual ~SeriesCrawler();



        /*!
         * Collects the column id stored in this container.
         * @return vector of columns
         */
        vector<C> columns() const;


        /*!
         * collects the index keys across all stored series performing a union set operation.
         * @return set with all the keys present across all series in the container.
         */
        set<K> keys(bool only_intersection=false) const;

        void fill_missing();
/*!
 * Entry point to sort all the included series using a provided comparator
 * @param fcomp comparator function
 */
        void apply_sort(function<void(const K&, const K&)> fcomp);
/*!
 * Removes all keys in the included series not included in the global _index of the super class.
 */
        void delete_sparse_rows();

        template<class T>
        void add_column(const C& columnid,  const Series<K,T>& p);

        void delete_column(const C& colid);

        template<class T>
        void add_column(const C& columnid,  Series<K,T>&& p);

        void clear();
    private:
        template<class T>
        void fill_missing_imp(set<K>& index);

        template<class T>
        void apply_sort_imp();

        template<class T>
        void delete_sparse_rows_imp(const set<K>& index);

        template<class T>
        void keys_imp(set<K>& keys, bool only_intersection) const;

        template<class T>
        void columns_imp(vector<C>& colids) const;

    };


}}

#include "seriescrawler.tcc"
#endif //GLOBAL_SERIESCRAWLER_HPP
