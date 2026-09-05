#include "twoSum/twoSum.h"

#include <iostream>

int main() {
    // Pair testing
    using R1 = twosum<9, value_list<int, 1, 2, 3, 4, 5, 6, 7>>::result;
    static_assert(R1::first + R1::second == 9, "");
    std::cout << R1::first << " " << R1::second << '\n';

    using R2 = twosum<20, value_list<int, 1, 3, 5, 7, 9, 11, 13>>::result;
    static_assert(R2::first + R2::second == 20, "");
    std::cout << R2::first << " " << R2::second << '\n';

    using R3 = twosum<10, value_list<int, 5, 5, 7, 8>>::result;
    static_assert(R3::first + R3::second == 10, "");
    std::cout << R3::first << " " << R3::second << '\n';

    using R4 = twosum<0, value_list<int, -5, -2, 3, 5, 10>>::result;
    static_assert(R4::first + R4::second == 0, "");
    std::cout << R4::first << " " << R4::second << '\n';

    // No solution
    using R5 = twosum<100, value_list<int, 1, 2, 3, 4, 5>>::result;
    static_assert(std::is_same<R5, NoResult>::value, "");

    // Single element cannot form a pair
    using R6 = twosum<5, value_list<int, 5>>::result;
    static_assert(std::is_same<R6, NoResult>::value, "");

    // Empty list
    using R7 = twosum<5, value_list<int>>::result;
    static_assert(std::is_same<R7, NoResult>::value, "");
}