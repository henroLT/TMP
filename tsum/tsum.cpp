#include "tsum.h"

#include <iostream>

int main () {
    using R = twosum<9, type_list<1,2,3,4,5,6,7>>::result;
    static_assert(R::first + R::second == 9, "");
    
    std::cout << R::first << " " << R::second << std::endl;
    return 0;
}