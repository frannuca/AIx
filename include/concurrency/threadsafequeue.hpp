#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <future>
#include <thread>
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <memory>
#include <chrono>
#include <exception>
#include <limits>
#include "../custom_exceptions.hpp"
namespace AIX{
    namespace Concurrency{
        using namespace std;
       
        template<typename T>
        class ThreadSafeQueue{
            using TMutex = mutex;

            queue<T> _queue;
            TMutex  mtx;
            
            condition_variable data_cond;
            condition_variable empty_cond;
            
            public:          
            void push(const T& x);
            void push(T&& x);
            void get(T& x, uint timems=numeric_limits<uint>::max());
            shared_ptr<T> getp(uint timems=numeric_limits<uint>::max()) noexcept;   
            bool empty() const;          
            void waitForEmpty();   

        };

        template<typename T>
        void ThreadSafeQueue<T>::push(const T& x){
             unique_lock<TMutex> lck(mtx);            
             _queue.push(x);
             data_cond.notify_one();
        };

        template<typename T>
        void ThreadSafeQueue<T>::push(T&& x){
             unique_lock<TMutex> lck(mtx);             
             _queue.push(std::move(x));
             data_cond.notify_one();
        }
        

        template<typename T>
        void ThreadSafeQueue<T>::get(T& x,uint timems){
            unique_lock<TMutex> lck(mtx);
           
            auto pred = [this](){return !_queue.empty();};
            if(!data_cond.wait_for(lck,chrono::milliseconds(timems),[this](){return !_queue.empty();})){
                throw TimeOutException("Time Out in 'bool ThreadSafeQueue<T>::push(T&& x,uint timems)'");
            }
                
            
            x = _queue.front();
            _queue.pop();   
            if(_queue.empty()){
                empty_cond.notify_all();
            }         
        }

        template<typename T>
        shared_ptr<T> ThreadSafeQueue<T>::getp(uint timems) noexcept{
            unique_lock<TMutex> lck(mtx);
           
            auto pred = [this](){return !_queue.empty();};
            
            if(!data_cond.wait_for(lck,chrono::milliseconds(timems),[this](){return !_queue.empty();})){
                return nullptr;
            }
            shared_ptr<T> x(new T(_queue.front()));
            _queue.pop();
            if(_queue.empty()){
                empty_cond.notify_all();
            }
            return x;  
        }

        template<typename T>
        bool ThreadSafeQueue<T>::empty() const{
            unique_lock<TMutex> lck(mtx);
            return _queue.empty();
        }

        template<typename T>
        void ThreadSafeQueue<T>::waitForEmpty(){            
            unique_lock<TMutex> lck(mtx);                       
            empty_cond.wait(lck,[this](){return _queue.empty();});                
        }
    }
}
#endif