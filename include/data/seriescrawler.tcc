namespace AIX{namespace Data {
        template<typename K, typename C, class ... Ts>
        SeriesCrawler<K,C,Ts...>::~SeriesCrawler(){
            cout<<"Destroying Frame"<<endl;
            clear();
        }

        template<typename K, typename C, class ... Ts>
        vector<C> SeriesCrawler<K,C,Ts...>::columns() const
        {
            vector<C> colids;
            (..., columns_imp<Ts>(colids));
            return colids;
        }

        template<typename K, typename C, class ... Ts>
        set<K> SeriesCrawler<K,C,Ts...>::keys() const{
            set<K> keys;
            (...,keys_imp<Ts>(keys));
            return keys;
        }

        template<typename K, typename C, class ... Ts>
        void SeriesCrawler<K,C,Ts...>::fill_missing(){
            set<K> ks = keys();
            (..., fill_missing_imp<Ts>(ks));
        }

        template<typename K, typename C, class ... Ts>
        void SeriesCrawler<K,C,Ts...>::apply_sort(function<void(const K&, const K&)> fcomp)
        {
            _fcomp = fcomp;
            (..., apply_sort_imp<Ts>());
        }

        template<typename K, typename C, class ... Ts>
        void SeriesCrawler<K,C,Ts...>::delete_sparse_rows()
        {
            set<K> ks = keys();
            (..., delete_sparse_rows_imp<Ts>(ks));
        }

        template<typename K, typename C, class ... Ts>
        template<class T>
        void SeriesCrawler<K,C,Ts...>::add_column(const C& columnid,  const Series<K,T>& p){
            if(_items<T>.find(this)==_items<T>.end()){
                _items<T>[this];
                _clear_functions.push_back([](const type* p){_items<T>.erase(p);});
                _copy_functions.push_back([](const type& from, type& to){
                    _items<T>[&to] = _items<T>[&from];
                });
                _copy_functions_move.push_back([](type&& from, type& to){
                    _items<T>[&to] = move(_items<T>[&from]);
                });

            }
            _delete_column_function[columnid] = [](const type* p,const C& colid){
                cout<<"Deleting "<<colid<<endl;
                _items<T>[p].erase(colid);
            };
            _items<T>[this][columnid]=p;
        }

        template<typename K, typename C, class ... Ts>
        void SeriesCrawler<K,C,Ts...>::deletecolumn(const C& colid){
            const function<void(const type*,const C&)>& f = _delete_column_function[colid];
            f(this,colid);
        }

        template<typename K, typename C, class ... Ts>
        template<class T>
        void SeriesCrawler<K,C,Ts...>::add_column(const C& columnid,  Series<K,T>&& p){

            if( _items<T>.find(this)== _items<T>.end()){
                _items<T>[this];
                _clear_functions.push_back([](const type* p){_items<T>.erase(p);});
            }
            _delete_column_function[columnid]=[](const type* p,const C& colid){
                _items<T>[p].erase(colid);
            };
            _items<T>[this][columnid]=move(p);
        }

        template<typename K, typename C, class ... Ts>
        void SeriesCrawler<K,C,Ts...>::clear(){
            for(auto& f: _clear_functions) f(this);
        }

        template<typename K, typename C, class ... Ts>
        template<class T>
        void SeriesCrawler<K,C,Ts...>::fill_missing_imp(set<K>& index){
            for(auto& c_series: _items<T>[this]){
                c_series.second.fill_missing(index);
            }
        }

        template<typename K, typename C, class ... Ts>
        template<class T>
        void SeriesCrawler<K,C,Ts...>::apply_sort_imp(){
            for(auto& kv: _items<T>[this]){
                Series<K,T> &x = kv.second;
                x.sortbykeyWith(_fcomp);
            }
        }

        template<typename K, typename C, class ... Ts>
        template<class T>
        void SeriesCrawler<K,C,Ts...>::delete_sparse_rows_imp(const set<K>& index){
            for(auto& kv: _items<T>[this]){
                Series<K,T> &x = kv.second;
                x.align_index(index);
            }
        }

        template<typename K, typename C, class ... Ts>
        template<class T>
        void SeriesCrawler<K,C,Ts...>::keys_imp(set<K>& keys) const {
            for(auto&kv: _items<T>[this]){
                auto& ks = kv.second.Keys();
                keys.insert(ks.begin(),ks.end());
            }
        }

        template<typename K, typename C, class ... Ts>
        template<class T>
        void SeriesCrawler<K,C,Ts...>::columns_imp(vector<C>& colids) const{
            auto& item_T = _items<T>[this];
            transform(item_T.begin(),item_T.end(),back_inserter(colids), [](auto& p){return p.first;});
        }

        template<typename K, typename C, class ... Ts>
        template<class T>
        map<const SeriesCrawler<K,C,Ts ...>*,map<C,Series<K,T> > > SeriesCrawler<K,C,Ts ...>::_items;

    }
}