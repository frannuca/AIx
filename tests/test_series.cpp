#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <experimental/type_traits>
#include <any>
#include <type_traits>
#include "data/series.hpp"
#include <iostream>
struct foo {
  int    memfun1(int a) const { return a;   }
  double memfun2(double b) const { return b; }
};

struct AAAA{
        int x;
        
        friend std::ostream& operator<<(std::ostream& os, const AAAA& x);
    };
    std::ostream& operator<<(std::ostream& os, const AAAA& o){
        os<<"("<<o.x<<")";
        return os;
    }

    bool operator<(const AAAA& a,const AAAA& b){return a.x<b.x;}

int main()
{
    std::cout<<"missing for double "<<AIX::Missing::get_missing<double>(0)<<std::endl;
    std::cout<<"missing for int "<<AIX::Missing::get_missing<int>(0)<<std::endl;
    std::cout<<"missing for string "<<AIX::Missing::get_missing<std::string>(0)<<std::endl;
    // std::any a = 1;
    // int& x = std::any_cast<int&>(a);
    // x=2;
    // std::cout<<"the value x="<<x<<std::endl;
    // std::cin>>x;
    // std::cout<<"the value x="<<x<<std::endl;

    // AIX::Data::Frame<int,std::string> frame;

    AIX::Data::Series<std::string,double> series1, series2;
    series1
        .add_item("one",1.0)
        .add_item("two",2.0)
        .add_item("three",3.0)
        .add_item("four",4.0)
        .add_item("five",5.0)
        .add_item("six",6.0)
        .add_item("seven",7.0)
        .add_item("eight",8.0)
        .add_item("nine",9.0)
        .add_item("ten",10.0);

    series2
        .add_item("one_",1.0)
        .add_item("two_",2.0)
        .add_item("three",3.0)
        .add_item("four",4.0)
        .add_item("five",5.0)
        .add_item("six",6.0)
        .add_item("seven",7.0)
        .add_item("eight",8.0)
        .add_item("nine_",9.0)
        .add_item("ten_",10.0);
    series1.sortbykey();
    series2.sortbykey();
    AIX::Data::Series<std::string,double> sumseries = (series1+series2)/series1*10.0;
    AIX::Data::Series<std::string,double>::const_iterator piter = series1.begin();
    // std::cout<<*piter<<std::endl;
    AIX::Data::Series<std::string,double> sumseries2 = 10.0/(sumseries/10.0);

    // std::cout<<"sorting data ascending"<<std::endl;
    // series1.sortbykey();
    for(auto& k:sumseries){
        std::cout<<k<<" -> "<<sumseries[k]<<std::endl;
    }
    
    AIX::Data::Series<AAAA,std::string> xseries;
    xseries.add_item(AAAA{0},"1000.0").add_item(AAAA{1},"1001");

    AIX::Data::Series<AAAA,std::string> yseries;
    yseries.add_item(AAAA{1},"2001.0").add_item(AAAA{2},"2002");

    auto stot = (xseries+yseries);
     for(auto& k:stot){
        std::cout<<k<<" -> "<<stot[k]<<std::endl;
    }
    // std::cout<<"one="<<series1["one"]<<std::endl;
    // const double& cd = series1["ten"];
    // double & vd = series1["nine"];
    // std::cout<<"nine="<<vd<<std::endl;
    

}