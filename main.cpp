#include "utils/random.h"
#include <iostream>

using namespace arena;

int main()
{
    std::cout << random::get(3, 6) << '\n';
}
