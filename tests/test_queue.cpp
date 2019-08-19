
#include "concurrency/threadsafequeue.hpp"
#include "concurrency/scheduler.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <chrono>


//main program test
using namespace AIX;
int main(int, char**) {
    
    Concurrency::ThreadSafeQueue<double> tsqueue;
    tsqueue.push(1.0);
    tsqueue.push(2.0);
    double one;
    tsqueue.get(one,100);
    auto twop = tsqueue.getp(100);
    std::cout<<"one="<<one<<std::endl;
    std::cout<<"two="<<*twop<<std::endl;

    Concurrency::Scheduler<void>& scheduler= Concurrency::getScheduler<void>();    
    std::vector<std::future<void>> fos;
    auto time0 = std::chrono::steady_clock::now();
    std::vector<std::future<void>> v;
    for(int i=0;i<10;++i){        
        std::ostringstream msg;
        msg<< "Item "<<i;
        std::string str = msg.str();
        v.push_back(scheduler.push([str](){std::this_thread::sleep_for(std::chrono::milliseconds(1000));std::cout<<str<<std::endl;}));
    }
    std::cout<<"inititing waitforcompletion"<<std::endl;
    scheduler.waitForEmptyQueue();
    for(auto& x:v) x.get();

    std::cout<<"finished waitforcompletion"<<std::endl;
    auto time1 = std::chrono::steady_clock::now();
    std::cout<<"time elapsed "<<std::chrono::duration_cast<std::chrono::milliseconds>(time1-time0).count()<<"ms"<<std::endl;
    
    std::cout << "OK";
}