#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <experimental/type_traits>
#include <any>
#include <type_traits>
#include "data/series.hpp"
#include "data/frame.hpp"
#include <iostream>
#include <boost/date_time.hpp>
#include <utility>
#include <iomanip>
#include "utils.hpp"

using namespace boost::gregorian;
using namespace std;

int main()
{
    
    std::cout<<"Starting Frame tests ...."<<std::endl;
    std::cout<<"Testing ctors"<<std::endl;
    
    std::cout<<"Checking defaut ctor ..."<<std::endl;
    AIX::Data::Frame<date,string,double,int,bool> frame;
    
    AIX::Data::Series<date,double> series_d;
    series_d.add_item(date(2019,01,01),1.0).add_item(date(2019,01,02),2.0).add_item(date(2019,01,03),3.0);
    
    AIX::Data::Series<date,int> series_i;
    series_i.add_item(date(2019,01,01),10);
    
    AIX::Data::Series<date,bool> series_b;
    series_b.add_item(date(2019,01,01),true).add_item(date(2019,01,02),false);


    frame.add_column("DoubleCol",series_d);
    frame.add_column("IntegerCol",series_i);
    frame.add_column("BoolCol",series_b);

    frame.add_column("DoubleCol2",series_d);
    frame.add_column("IntegerCol2",series_i);
    frame.add_column("BoolCol2",series_b);

    frame.add_column("ToBeDeleted",series_b);
    for(auto c:frame.columns()) cout<<c<<endl;
    cout<<"--------------------------------"<<endl;
    frame.deletecolumn("ToBeDeleted");
    for(auto c:frame.columns()) cout<<c<<endl;

    auto& s1 = frame.getColumn<double>("DoubleCol");
    cout<<s1<<endl;

    frame.add_column("DoubleSum",frame.getColumn<double>("DoubleCol")+frame.getColumn<double>("DoubleCol2"));

    vector<string> columns = frame.columns();
    for(auto c:columns) cout<<c<<endl;


    auto& s2 = frame.getColumn<double>("DoubleSum");
    cout<<s2<<endl;

    auto index = frame.keys();
    cout<<"INDEX"<<endl;
    for(auto idx:index){
        cout<<idx<<endl;
    }

    frame.fill_missing();
    frame.delete_sparse_rows();

    frame.join(frame);

    assert(frame == frame);

    AIX::Data::Frame<date,string,double,int,bool> frame2;
    frame2 = frame;

    AIX::Data::Frame<date,string,double,int,bool> frame3=frame;
    AIX::Data::Frame<date,string,double,int,bool> frame4(frame);
    AIX::Data::Frame<date,string,double,int,bool> frame5(move(frame4));

    auto index2 = frame2.keys();
    cout<<"INDEX2"<<endl;
    for(auto idx:index2){
        cout<<idx<<endl;
    }


    AIX::Data::Series<date,double>& series_frame2 = frame2.getColumn<double>("DoubleSum");
    series_frame2[date(2019,01,01)] = 98766789.0;
    assert(frame != frame2);
    assert(frame == frame3);
    assert(frame == frame5);
    assert(frame4.columns().size()==0);
    std::cout<<"OK"<<std::endl;

}