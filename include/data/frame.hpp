#ifndef FRAME_H
#define FRAME_H
#include <vector>
#include <algorithm>

namespace AIX{
    namespace Data{
        template<typename K,typename C>
        class Frame{
            
            std::vector<K> _index;
            std::vector<C> _columns;
            
            public:
             Frame():{};
            
        }
    }
}
#endif