#ifndef FRAME_H
#define FRAME_H
#include <map>
#include <set>
#include <any>
#include <functional>
#include "series.hpp"
#include <memory>
#include <algorithm>
#include "seriescrawler.hpp"

namespace AIX{
    namespace Data{
    using namespace std;

    template<typename K, typename C, class ... Ts>
    class Frame: public SeriesCrawler<K,C,Ts ...>{
        private:
        using base_type = SeriesCrawler<K,C,Ts ...>;
        using TFrame = Frame<K,C,Ts ...>;

        public:
        Frame(){};
        ~Frame(){}

        Frame(const TFrame& that):base_type(that){};
        Frame(TFrame&& that):base_type(forward<base_type>(that)){};


        TFrame& operator=(const TFrame& that){this->base_type::operator=(that); return *this;}
        TFrame& operator=(TFrame&& that) noexcept {return this->base_type::operator=(forward<TFrame>(that));};

        bool operator==(const TFrame& that) const;
        bool operator!=(const TFrame& that) const;

        template<class T>
        Series<K,T>& getColumn(const C& colid);

        void join( Frame<K,C,Ts ...>& that);

    private:
        template<class T>
        void equalseries(const TFrame& that, bool &ok) const;
        template<class T>
        void joinImp( Frame<K,C,Ts ...>& that);
    };

}}

#include "frame.tcc"
#endif