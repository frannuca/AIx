namespace AIX{namespace Data{



        template<class K, class C, class ... Ts>
        template<class T>
        void Frame<K,C,Ts...>::joinImp( Frame<K,C,Ts ...>& that){
            auto& thismap = this->base_type::template _items<T>[this];
            auto& thatmap = this->base_type::template _items<T>[&that];

            for(auto& kv: thatmap){
                thismap[kv.first] = kv.second;
            }
        };


        template<class K, class C, class ... Ts>
        template<class T>
        Series<K,T>& Frame<K,C,Ts...>::getColumn(const C& colid){
            return this->base_type::template _items<T>[this][colid];
        }

        template<class K, class C, class ... Ts>
        void Frame<K,C,Ts...>::join( Frame<K,C,Ts ...>& that)
        {
            (..., joinImp<Ts>(that));
        }

        template<class K, class C, class ... Ts>
        bool Frame<K,C,Ts...>::operator==(const TFrame& that) const{
            auto thiscolumns = this->base_type::columns();
            auto thatcolumns = that.columns();
            if(!equal(thiscolumns.begin(),thiscolumns.end(),thatcolumns.begin(),thatcolumns.end())){
                return false;
            }
            bool ok=true;
            (..., equalseries<Ts>(that,ok));
            return ok;
        }

        template<class K, class C, class ... Ts>
        bool Frame<K,C,Ts...>::operator!=(const TFrame& that) const{
            return !(*this == that);
        }

        template<class K, class C, class ... Ts>
        template<class T>
        void Frame<K,C,Ts...>::equalseries(const TFrame& that, bool &ok) const {
            auto& s1 = this->base_type::template _items<T>[this];
            auto& s2 = that.base_type::template _items<T>[&that];
            if(!ok) return;
            for(auto& kv:s1){

                if(s2.find(kv.first) == s2.end()){
                    ok = false;
                }
                const Series<K,T>& a = s1[kv.first];
                const Series<K,T>& b = s2[kv.first];

                ok &= a == b;
            }
        }
}}