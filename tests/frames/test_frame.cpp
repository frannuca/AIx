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
   
    frame.addColumn("DoubleCol",series_d);
    frame.addColumn("IntegerCol",series_i);
    frame.addColumn("BoolCol",series_b);

    frame.addColumn("DoubleCol2",series_d);
    frame.addColumn("IntegerCol2",series_i);
    frame.addColumn("BoolCol2",series_b);

    frame.addColumn("ToBeDeleted",series_b);
    for(auto c:frame.getColsIndex()) cout<<c<<endl;
    cout<<"--------------------------------"<<endl;
    frame.deletecolumn("ToBeDeleted");
    for(auto c:frame.getColsIndex()) cout<<c<<endl;

    auto& s1 = frame.getColumn<double>("DoubleCol");
    cout<<s1<<endl;

    frame.addColumn("DoubleSum",frame.getColumn<double>("DoubleCol")+frame.getColumn<double>("DoubleCol2"));

    vector<string> columns = frame.getColsIndex();
    for(auto c:columns) cout<<c<<endl;


    auto& s2 = frame.getColumn<double>("DoubleSum");
    cout<<s2<<endl;

    auto index = frame.getRowIndex();
    cout<<"INDEX"<<endl;
    for(auto idx:index){
        cout<<idx<<endl;
    }

    frame.fillMissingValues();
    frame.removeSparseRows();
    
    std::cout<<"OK"<<std::endl;

}