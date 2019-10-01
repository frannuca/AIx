#ifndef FRAME_H
#define FRAME_H
#include <map>
#include <set>
#include <any>
#include <functional>
#include "series.hpp"
#include <memory>
#include <algorithm>

namespace AIX{
    namespace Data{
    using namespace std;

    template<typename K, typename C, class ... Ts>
    class Frame{
        private:
        using TFrame = Frame<K,C,Ts ...>;
        function<bool(const K&, const K&)> _fcomp = less<K>();
        vector<K> _index;
        template<class T>
        static map<const TFrame*,map<C,Series<K,T> > > _items;
        vector<function<void(const TFrame*)> > _clear_functions;
        map<C,function<void(const TFrame*,const C&)> > _delete_column_function;
        vector<function<void(const TFrame& from, TFrame& to)> >  _copy_functions;
        
        void sortSeries(function<bool(const K&, const K&)> fcomp)
        {   
            (..., sortseriesimp<Ts>(fcomp));
        };

        template<class T>
        void sortseriesimp(function<bool(const K&, const K&)> fcomp){
            for(auto& kv: _items<T>[this]){
                Series<K,T> &x = kv.second;
                x.sortbykeyWith(fcomp);
            }
            
        };

        void removeMissing()
        {   set<K> keys;
            getKeys(keys);
            vector<K> vkeys(keys.begin(),keys.end());
            (..., removeMissingImp<Ts>(vkeys));
        };

        template<class T>
        void removeMissingImp(const vector<K>& index){
            for(auto& kv: _items<T>[this]){
                Series<K,T> &x = kv.second;
                x.alignwithindex(index);
            } 
        };

        void fillMissing()
        {   set<K> keys;
            getKeys(keys);
            vector<K> vkeys(keys.begin(),keys.end());
            (..., fillMissingImp<Ts>(vkeys));
        };

        template<class T>
        void fillMissingImp(const vector<K>& index){
            for(auto& kv: _items<T>[this]){
                Series<K,T> &x = kv.second;
                x.fillMissing(index);
            } 
        };

        void getColumns(vector<C>& colids)
        {   
            (..., pullColumnNames<Ts>(colids));
        };

        template<class T>
        void pullColumnNames(vector<C>& colids){
            auto& item_T = _items<T>[this];
            transform(item_T.begin(),item_T.end(),back_inserter(colids), [](auto& p){return p.first;});
        };

        void getKeys(set<K>& keys){
            (...,pullIndexes<Ts>(keys));
        }

        template<class T>
        void pullIndexes(set<K>& keys){
            for(auto&kv: _items<T>[this]){
                    auto& ks = kv.second.Keys();
                    keys.insert(ks.begin(),ks.end());
            }   
        }

    

        void sortByKey(){
            sortSeries(_fcomp);
        }

        void sortByKey(function<bool(const K&, const K&)> fcomp){
            _fcomp = fcomp;
            sortByKey();
        }
    
        public:
        Frame(){};
        ~Frame(){clear();}

        vector<C> getColsIndex(){
            vector<C> cols;
            getColumns(cols);
            return cols;
        }
        vector<K> getRowIndex(){
            set<K> a;
            getKeys(a);
            return vector<K>(a.begin(),a.end());
        }
        
        void order(){
            sortByKey();
        }
        void orderWith(function<bool(const K&, const K&)> fcomp){
            sortByKey(fcomp);
        }

        template<class T>
        void addColumn(const C& columnid,  const Series<K,T>& p){
            if(_items<T>.find(this)==_items<T>.end()){
                 _items<T>[this];
                 _clear_functions.push_back([](const TFrame* p){_items<T>.erase(p);});
                 _copy_functions.push_back([](const TFrame& from, TFrame& to){
                    _items<T>[&to] = _items<T>[&from];
                 });
                 
            }
            _delete_column_function[columnid] = [](const TFrame* p,const C& colid){
                     cout<<"Deleteing "<<colid<<endl;
                     _items<T>[p].erase(colid);
                     };
            _items<T>[this][columnid]=p;
        };

        TFrame& operator=(const TFrame& that){
            for(auto& f: _copy_functions) f(*this,that);
        };

        template<class T>
        void addColumn(const C& columnid,  Series<K,T>&& p){
           if(_items<T>.find(this)==_items<T>.end()){
                 _items<T>[this];
                 _clear_functions.push_back([](const TFrame* p){_items<T>.erase(p);});
            }
             _delete_column_function[columnid]=[](const TFrame* p,const C& colid){
                     
                     _items<T>[p].erase(colid);};
            _items<T>[this][columnid]=move(p);
        };

        template<class T>
        Series<K,T>& getColumn(const C& colid){

            return _items<T>[this][colid];
        }
        void deletecolumn(const C& colid){
            function<void(const TFrame*,const C&)>& f = _delete_column_function[colid];
            f(this,colid);
        }
        void fillMissingValues(){
            fillMissing();
        }

        void removeSparseRows(){
            removeMissing();
        }
        void clear(){
            for(auto& f: _clear_functions) f(this);
        }
    };
    template<typename K, typename C, class ... Ts>
    template<class T>
    map<const Frame<K,C,Ts ...>*,map<C,Series<K,T> > > Frame<K,C,Ts ...>::_items;
}}
#endif