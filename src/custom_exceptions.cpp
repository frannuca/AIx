#include "custom_exceptions.hpp"

namespace AIX{
            TimeOutException::TimeOutException(const char* msg):msg_(msg){};
            TimeOutException::TimeOutException(const string& msg):msg_(msg){};
            TimeOutException::~TimeOutException() throw(){};
            const char* TimeOutException::what() const noexcept {return msg_.c_str();};

}