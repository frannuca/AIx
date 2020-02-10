namespace AIX{namespace Data {

        template<class K,class T>
        void Series<K,T>::order() {
            sort(_index.begin(), _index.end(), _fcomp);
            isSorted = true;
        }

        template<class K,class T>
        void Series<K,T>::orderWith(decltype(_fcomp) fcomp){
            _fcomp=fcomp;
            order();
        }

        template<class K,class T>
        void Series<K,T>::throwForExistingKey(const K& k){
            if(_data.find(k)!=_data.end()){
                ostringstream msg;
                msg<<"The key"<<k<<" is already part of the Series index";
                throw invalid_argument(msg.str());
            }
        }

        template<class K,class T>
        int Series<K,T>::locate(const K& k){
            typename vector<K>::iterator nlow, nhigh;
            if(isSorted){
                typename vector<K>::iterator nlow, nhigh;
                tie(nlow,nhigh)=equal_range(_index.begin(),_index.end(),k,_fcomp);
                if(distance(nlow,nhigh)==1){
                    return distance(_index.begin(),nlow);
                }
                else{
                    return -1;
                }
            }
            else{
                auto piter = std::find(_index.begin(),_index.end(),k);
                if(piter == _index.end())
                    return -1;
                else
                    return std::distance(_index.begin(),piter);
            }

        }

        template<class K,class T>
        size_t Series<K,T>::updateIndex(const K& k){
            int n=-1;
            if(isSorted){
                typename vector<K>::iterator nlow, nhigh;
                tie(nlow,nhigh)=equal_range(_index.begin(),_index.end(),k,_fcomp);
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

        template<class K,class T>
        Series<K,T> Series<K,T>::applyBinaryOp(const Series<K,T>& a, const Series<K,T>& b, function<T(const T&, const T&)> ops){
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

        template<class K,class T>
        Series<K,T> Series<K,T>::applyBinaryOp(const Series<K,T>& a, const T& l, function<T(const T&, const T&)> ops){
            vector<K> keys =a.Keys();


            Series<K,T> sumseries;
            for(auto& k:keys){
                sumseries.add_item(k,ops(a[k],l));
            }

            return sumseries;
        }

        template<class K,class T>
        Series<K,T> Series<K,T>::applyUnaryOp(const Series<K,T>& a, function<T(const T&)> ops){

            Series<K,T> sumseries;
            for(auto& k:a){
                sumseries.add_item(k,ops(a[k]));
            }

            return sumseries;
        }

        template<class K,class T>
        Series<K,T>& Series<K,T>::operator=(const Series<K,T>& that){
            this->_data = that._data;
            this->_index = that._index;
            return *this;
        }

        template<class K,class T>
        void Series<K,T>::clear(){
            _data.clear();
            _index.clear();
        }

        template<class K,class T>
        Series<K,T>& Series<K,T>::operator=(Series<K,T>&& that){
            this->_data = move(that._data);
            this->_index = move(that._index);
            return *this;
        }

        template<class K,class T>
        void Series<K,T>::fill_missing(const set<K>& xaxis){
            for(const K& k: xaxis){
                if(hasKey(k)) continue;
                add_item(k,Missing::get_missing<T>(0));
            }
        }

        template<class K,class T>
        void Series<K,T>::align_index(const set<K>& xaxis){
            for(const K& k: _index){
                if(find(xaxis.begin(),xaxis.end(),k)==xaxis.end()){
                    remove_item(k);
                }
            }
        }

        template<class K,class T>
        bool Series<K,T>::operator==(const Series<K,T>& that) const {
            return std::equal(_index.begin(),_index.end(),that._index.begin(),that._index.end()) &&
                   std::equal(_data.begin(),_data.end(),that._data.begin(),that._data.end());

        }

        template<class K,class T>
        bool Series<K,T>::operator !=(const Series<K,T>& that) const{
            return !(*this == that);
        }

        template<class K,class T>
        Series<K,T>& Series<K,T>::add_item(const K& k, const T& v){
            throwForExistingKey(k);
            _data[k]=v;
            updateIndex(k);

            return *this;
        }

        template<class K,class T>
        Series<K,T>& Series<K,T>::add_item(const K& k,  T&& v){
            throwForExistingKey(k);
            _data[k]=move(v);
            updateIndex(k);

            return *this;
        }

        template<class K,class T>
        Series<K,T>& Series<K,T>::add_item(const pair<K,T>& x){
            throwForExistingKey(x.first);
            _data.insert(x);
            updateIndex(x.first);
            return *this;
        }
        template<class K,class T>
        bool Series<K,T>::hasKey(const K& k) const{

            return _data.find(k)!=_data.end();
        }

        template<class K,class T>
        Series<K,T>& Series<K,T>::add_items(const vector<pair<K,T> >& x){
            for(const pair<K,T>& kv: x){
                add_item(kv);
            }

            return *this;
        }

        template<class K,class T>
        Series<K,T>& Series<K,T>::add_items(const vector<K>& keys, const vector<T>& v){
            assert(keys.size()==v.size());
            for(size_t i=0;i<keys.size();++i)
            {
                add_item(keys[i],v[i]);
            }
            return *this;
        }

        template<class K,class T>
        void Series<K,T>::join(const Series<K,T>& series,bool overridevalues){
            for(const auto& k:series)
            {   bool haskey = hasKey(k);
                if(overridevalues && haskey){ _data[k]= series[k];}
                else if(!haskey){
                    add_item(k,series[k]);
                }
            }
        }

        template<class K,class T>
        bool Series<K,T>::remove_item(const K& k){
            int n = locate(k);
            if(n>=0) {
                _index.erase(_index.begin()+n);
                return true;
            }
            return false;
        }

        template<class K,class T>
        const vector<K>& Series<K,T>::sortbykey(){
            if(!isSorted){
                order();
            }
            return _index;
        }

        template<class K,class T>
        const vector<K>& Series<K,T>::sortbykeyWith(function<bool(const K&,const K&)> fcomp){
            orderWith(fcomp);
            return _index;
        }

        template<class K,class T>
        T& Series<K,T>::operator[](const K& k){
            return _data[k];
        }

        template<class K,class T>
        T Series<K,T>::operator[](const K& k) const{
            T a = _data[k];
            return a;
        }

        template<class K,class T>
        std::ostream& operator<<(ostream& out, const Series<K,T>& series){
            for(const K& k: series.Keys())
            {
                out<<k<<","<<series[k]<<std::endl;
            }
            return out;
        }

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
            return series.inv()*l;
        }
    }
}