#if !defined(PITO_RANDOM_H)
#define PITO_RANDOM_H

#include <random>
#include <chrono>

namespace arena::random
{
    inline const auto get_time()
    {
        return std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
    
    inline std::random_device rd{};
    inline std::mt19937 rand_engine{
        static_cast<std::mt19937::result_type>(get_time())
    }; 

    // redundante mas é pra ficar alinhado bonitinho
    extern int get(int x, int y) 
    {
        return std::uniform_int_distribution{x,y}(rand_engine);
    }
}


#endif
