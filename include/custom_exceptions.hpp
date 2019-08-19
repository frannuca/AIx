#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <future>
#include <thread>
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <memory>
#include <chrono>
#include <exception>
#include <limits>

namespace AIX{
    
        using namespace std;

        class TimeOutException: public exception{
            public:
            explicit TimeOutException(const char* msg);
            explicit TimeOutException(const string& msg);
            virtual ~TimeOutException() throw();
            virtual const char* what() const noexcept;

            protected:
              std::string msg_;
        };

    
}
#endif        