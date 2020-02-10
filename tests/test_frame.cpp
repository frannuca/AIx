#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <experimental/type_traits>
#include <any>
#include <type_traits>
#include "../include/data/series.hpp"
#include "../include/data/frame.hpp"
#include <iostream>
#include <boost/date_time.hpp>
#include <utility>
#include <iomanip>
#include "../include/utils.hpp"

using namespace boost::gregorian;
using namespace std;

int main()
{
    
    cout<<"Starting Frame tests ...."<<endl;

    cout<<"Testing ctor"<<endl;

    AIX::Data::Frame<date,string,double,int,bool,string> frame;
    auto d1 = date(2019,01,01);
    auto d2 = date(2019,01,02);
    auto d3 = date(2019,01,03);
    vector<date> dates = {d1,d2,d3};
    //columns are Series, creating series to be added:
    AIX::Data::Series<date,double> series_d;
    series_d
    .add_item(dates[0],1.0)
    .add_item(dates[1],2.0)
    .add_item(dates[2],3.0);
    
    AIX::Data::Series<date,int> series_i;
    series_i
    .add_item(dates[1],10)
    .add_item(dates[2],10);
    
    AIX::Data::Series<date,bool> series_b;
    series_b
    .add_item(dates[0],true)
    .add_item(dates[1],false);

    AIX::Data::Series<date,string> series_str;
    series_str
    .add_item(dates[1],"1")
    .add_item(dates[2],"2");

    frame.add_column("double",series_d);
    frame.add_column("bool",series_b);
    frame.add_column("string",series_str);
    frame.add_column("int",series_i);

    cout<<"checking index completeness"<<endl;
    set<date> keys = frame.keys();
    assert(std::equal(dates.begin(),dates.end(),keys.begin(),keys.end()));

    cout<<"Checking columns"<<endl;
    vector<string> columns = {"double","bool","string","int"};
    sort(columns.begin(),columns.end());

    vector<string> framecolumns = frame.columns();
    sort(framecolumns.begin(),framecolumns.end());
    assert(equal(columns.begin(),columns.end(),framecolumns.begin(),framecolumns.end()));

    cout<<"Checking delete column"<<endl;
    auto series_x2 = series_d*2;
    frame.add_column("2x",series_x2);
    frame.delete_column("2x");
    framecolumns = frame.columns();
    sort(framecolumns.begin(),framecolumns.end());
    assert(equal(columns.begin(),columns.end(),framecolumns.begin(),framecolumns.end()));


    cout<<"checking retrieval of columns as series"<<endl;
    auto& s1 = frame.getColumn<double>("double");
    assert(s1 == series_d);
    auto& s2 = frame.getColumn<bool>("bool");
    assert(s2 == series_b);
    auto& s3 = frame.getColumn<string>("string");
    assert(s3 == series_str);
    auto& s4 = frame.getColumn<int>("int");
    assert(s4 == series_i);

    cout<<"Checking copy ctor and operator ="<<endl;

    AIX::Data::Frame<date,string,double,int,bool,string> frame2 = frame;
    assert(frame2 == frame);

    AIX::Data::Frame<date,string,double,int,bool,string> frame3(frame);
    assert(frame3 == frame);

    AIX::Data::Frame<date,string,double,int,bool,string> frame4(frame3);

    AIX::Data::Frame<date,string,double,int,bool,string> frame5 = move(frame3);
    assert(frame4 == frame);
    assert(frame3.columns().size()==0);

    cout<<"chekcing sparse removal"<<endl;
    frame.delete_sparse_rows();
    set<date> spares_keysa = frame.keys();
    vector<date> spares_keys(spares_keysa.begin(),spares_keysa.end());

    set<date> survialkeysb = {dates[1]};
    vector<date> survialkeys(survialkeysb.begin(),survialkeysb.end());

    assert(equal(spares_keys.begin(),spares_keys.end(),survialkeys.begin(),survialkeys.end()));

    frame2.fill_missing();
    set<date> allkeys = frame2.keys();
    assert(std::equal(dates.begin(),dates.end(),allkeys.begin(),allkeys.end()));

    assert(frame4 == frame5);
    frame4.getColumn<double>("double")[dates[0]] = 9999.9;
    assert(frame4 != frame5);

    cout<<"accessing a row"<<endl;
    auto rowSeries = frame4.row_generic(dates[1]);
    for(auto& d:rowSeries){
        cout<<d<<endl;
    }

    cout<<"accessing a row by type double"<<endl;
    frame4.add_column("double2",series_d);
    frame4.add_column("double3",series_d);
    AIX::Data::Series<string,double*> rowSeries2 = frame4.row<double>(dates[1]);

    cout<<rowSeries2<<endl;

    std::cout<<"OK"<<endl;

}