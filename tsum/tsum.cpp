#include "tsum.h"

int main () {
    static_assert(twosum<9,  type_list<1,2,3,4,5,6,7>>::value, "Nope");
    static_assert(twosum<14, type_list<1,2,3,4,5,6,7>>::value, "Nope"); // fails to compile

    return 0;
}