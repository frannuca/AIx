#ifndef AXIS_H
#define AXIS_H
#include <utility>

namespace AIX{namespace Data{

template<class K, class V>
class Axis{
            public:
            Axis()=delete;
            Axis(const Axis& ax);
            Axis(Axis&& ax);
            Axis(const K& x, const V& y);
            Axis(std::pair<K,V>& p);
            
            Axis& operator=(const Axis& that);
            bool operator<(const Axis& that) const;
            bool operator<=(const Axis& that) const;
            bool operator>(const Axis& that) const;
            bool operator>=(const Axis& that) const;
            
            bool operator==(const Axis& that) const;
            bool operator==(const K& that) const;
            const K& x() const;
            V& y();
            V y() const;
            V& operator*();

            operator K()  {return _x;}
            V operator*() const;

            template<class A, class B>
            friend bool operator<(const Axis<A,B>& op, const A& k);

            template<class A, class B>
            friend bool operator<(const A& k,const Axis<A,B>& op);

            private:
            K _x;
            V _y;
            
        };

        template<class K, class V>
        bool operator<(const Axis<K,V>& op, const K& k){
            return op._x<k; 
            };
        template<class K, class V>
        bool operator<(const K& k,const Axis<K,V>& op){
            return op<k;
        }

        template<class K, class V>
        Axis<K,V>::Axis(const Axis& ax):_x(ax._x),_y(ax._y){}

        
        template<class K, class V>
        Axis<K,V>::Axis(Axis&& ax):_x(ax._x),_y(ax._y){}
        
        template<class K, class V>
        Axis<K,V>::Axis(const K& x, const V& y):_x(x),_y(y){}
        
        template<class K, class V>
        Axis<K,V>::Axis(std::pair<K,V>& p):_x(p.first),_y(p.second){}
        
        template<class K, class V>
        Axis<K,V>& Axis<K,V>::operator=(const Axis& that){
            _x = that._x;
            _y=that._y;return *this;
            }

        template<class K, class V>
        bool Axis<K,V>::operator<(const Axis<K,V>& that) const {
            return _x<that._x;
            }

        template<class K, class V>
        bool Axis<K,V>::operator<=(const Axis<K,V>& that) const {
            return _x<=that._x;
            }


        template<class K, class V>
        bool Axis<K,V>::operator>(const Axis<K,V>& that) const {
            return _x>that._x;
            }

        template<class K, class V>
        bool Axis<K,V>::operator>=(const Axis<K,V>& that) const {
            return _x>=that._x;
            }

        template<class K, class V>
        bool Axis<K,V>::operator==(const Axis<K,V>& that) const {
            return _x==that._x;
            }
        
        template<class K, class V>
        bool Axis<K,V>::operator==(const K& that) const {
            return _x==that;
            }
        

        template<class K, class V>
        const K& Axis<K,V>::x() const {return _x;};

        template<class K, class V>
        V& Axis<K,V>::y(){return _y;}

        template<class K, class V>
        V Axis<K,V>::y() const{return _y;};

        template<class K, class V>
        V& Axis<K,V>::operator*(){
            return _y;
        }
        template<class K, class V>
        V Axis<K,V>::operator*() const{
            return _y;
        }

}}

#endif