#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <iostream>
#include "custom_exceptions.hpp"
#include <thread>
#include <mutex>
#include <functional>
#include <memory>
#include "threadsafequeue.hpp"
namespace cnn{
    namespace concurrency{
        template<typename T> class Scheduler;
        template<typename T> Scheduler<T>& getScheduler();

        template<typename T>
        class Scheduler{
            private:                
                using Action = function<T()>;
                using EntryData = shared_ptr<std::packaged_task<T()>>;
                                
                mutable bool _isRunning;
                mutable std::vector<std::thread> _threads;
                mutable ThreadSafeQueue<EntryData> _queue;
                mutable uint number_of_threads;
                void worker() const; 
                Scheduler(int num_threads=-1);   
                
                  
                void start() const;
                void stop() const;                       
            public:           
                  
                Scheduler(const Scheduler<T>&) = delete;
                Scheduler<T>& operator=(Scheduler<T>&) = delete;
                Scheduler(Scheduler<T>&&) = delete;

                std::future<T> push(Action f) const;                
                void waitForEmptyQueue() const;
                bool isRunning() const {return _isRunning;}
                ~Scheduler();  
                friend  Scheduler<T>& getScheduler<T>();
        };
                
        template<typename T>
        Scheduler<T>& getScheduler(){
           static std::unique_ptr<Scheduler<T>> local(new Scheduler<T>());
           return *local.get();
        }

        template<typename T>
        Scheduler<T>::Scheduler(int num_threads):_isRunning(false){            
            number_of_threads = (num_threads<=0)? std::thread::hardware_concurrency():num_threads;                        
            std::cout<<"SETTING SCHEDULER TO USE NTHREADS = "<<std::thread::hardware_concurrency();            
        }

        template<typename T>
        void Scheduler<T>::worker() const{ 
            while(_isRunning){            
                shared_ptr<EntryData> data = _queue.getp(500);            
                if(data)
                {
                    EntryData pp = *data;
                    packaged_task<T()>& task = *pp; 
                    task();                                       
                }
            }

            std::cout<<"Exiting Thread"<<std::this_thread::get_id()<<std::endl;            
        }

        template<typename T>
        void Scheduler<T>::start() const{     
            if(!_isRunning){
                _isRunning=true;
                for(uint i=0;i<number_of_threads;++i){
                    //_threads.push_back(std::thread([this](){this->worker();}));
                    _threads.push_back(std::thread(std::bind(&Scheduler<T>::worker,this)));
                }
            }            
        }

        template<typename T>
        void Scheduler<T>::stop() const{     
            if(_isRunning){
                _isRunning=false;                
                for(auto& th:_threads){
                    if(th.joinable())
                     th.join();
                }
            }                  
        }

        template<typename T>
        std::future<T> Scheduler<T>::push(Action f) const{  
            if(!_isRunning){
                start();
            }       
                          
            EntryData data(new std::packaged_task<decltype(f())()>(f));
            _queue.push(data);
            return data->get_future();            
        }

        template<typename T>
        Scheduler<T>::~Scheduler(){
            stop();
            
        }
        

        template<typename T>
        void Scheduler<T>::waitForEmptyQueue() const{
            _queue.waitForEmpty();
        }
    }
}
#endif