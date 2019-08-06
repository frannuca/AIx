#include "cnn.hpp"
namespace cnn{
    CNN::CNN():_number_of_outputs(-1){

    }
    size_t CNN::add_layer(const Layer& layer){
        _layers.push_back(layer);
        return _layers.size();

    }

    size_t CNN::add_ouput_layer(size_t number_of_outputs){
        _number_of_outputs = number_of_outputs;
        return _layers.size()+1;
    }
}
