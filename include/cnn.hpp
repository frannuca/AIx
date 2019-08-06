#ifndef CNN_H
#define CNN_H
#include <cstddef>
#include <vector>

namespace cnn{

    enum class CNN_LAYER_TYPE{
        CONVOLUTIONAL,
        MAXPOOL        
    };

    struct Layer{
        size_t filter_rows;
        size_t filter_cols;
        size_t number_of_filters; 
        CNN_LAYER_TYPE type;
    };

    class CNN{
        private:
            std::vector<Layer> _layers;
            size_t _number_of_outputs;
        public:
            CNN();
            size_t add_layer(const Layer& layer);
            size_t add_ouput_layer(size_t number_of_outputs);
    };
}
#endif