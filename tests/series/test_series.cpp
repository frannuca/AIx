#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <experimental/type_traits>
#include <any>
#include <type_traits>
#include "data/series.hpp"
#include <iostream>
#include <boost/date_time.hpp>
#include <utility>
#include <iomanip>
#include "utils.hpp"

using namespace boost::gregorian;

struct SWithOrder{
        int x;
        bool operator<(const SWithOrder& a){return x<a.x;}
    };
  
struct SWithoutOrder{
        int x;
        bool operator<(const SWithoutOrder& a){return x<a.x;}
    };
  
    

int main()
{
    std::cout<<"MISSING for Pointer="<<AIX::Missing::get_missing<int*>(0)<<std::endl;

    std::cout<<"Starting Series tests ...."<<std::endl;
    std::cout<<"Testing ctors"<<std::endl;
    
    std::cout<<"Checking defaut ctor ..."<<std::endl;
    AIX::Data::Series<date,double> series1;

    std::cout<<"Adding data..."<<std::endl;
    series1
        .add_item(date(2021,01,01),1.0)
        .add_item(date(2010,02,01),2.0);
        
    series1.add_items(std::vector<std::pair<date,double>>{std::make_pair(date(2019,03,01),3.0)});
    series1.add_items(std::vector<date>{date(2050,04,01)} , std::vector<double>{4.0});  
    
    std::cout<<"Testing copy ctor ..."<<std::endl;
    AIX::Data::Series<date,double> series2(series1);
    
    std::cout<<"Testing operator= ..."<<std::endl;
    AIX::Data::Series<date,double> series3;
    series3 = series2;

    std::cout<<"Testing equality in between objects"<<std::endl;
    assert(series1 == series2 && series2 == series3);

    std::cout<<"Sorting series"<<std::endl;
    series1.sortbykey();
    series2.sortbykey();
    series3.sortbykey();

    std::cout<<"Chekcing order (ascending)"<<std::endl;
    for(int i=1;i<series1.size();++i) assert(series1.Keys()[i-1]<series1.Keys()[i]);

    std::cout<<"Checking operations"<<std::endl;
    {
        auto ops1 = (series1+series2)/series1*10.0;
        for(auto& k:ops1){
            assert(std::abs(ops1[k]-20.0)<1e-6);
        }
    }
    {
        auto ops1 = 10.0*series1/(series1+series2);
        for(auto& k:ops1){
            assert(std::abs(ops1[k]-5.0)<1e-6);
        }
    }
    {
        auto ops1 = 10.0/(series1+series2);
        for(auto& k:ops1){
            assert(std::abs(ops1[k]-10.0/(2.0*series1[k]))<1e-6);
        }
    }
    
    {
        auto ops1 = series1*series2/(series1*series2);
        for(auto& k:ops1){
            assert(std::abs(ops1[k]-1.0)<1e-6);
        }
    }
    
    {
        auto ops1 = -series1 + series2;
        for(auto& k:ops1){
            assert(std::abs(ops1[k])<1e-6);
        }
    }
    //Compilation Error: HasLessThanOp 
    // struct obj{
    //      std::string a;
    //     //bool operator<(const obj& ){return true;};
    //  };
    // AIX::Data::Series<obj,double> wrongSeries;

    {
        auto d = date(2021,01,01);
        assert(series1.remove_item(d));

    }
    {
        auto d = date(2021,01,03);
        assert(!series1.remove_item(d));

    }


}