#include "twoSum/twoSum.h"

#include <iostream>

    int main() {
    // Pair testing
    using R1 = twosum<
        9,
        util::value_list<int, 1, 2, 3, 4, 5, 6, 7>
    >::result;
    static_assert(R1::size == 2, "Failure");
    static_assert(R1::at<0>::value + R1::at<1>::value == 9, "Failure");
    std::cout << "Target: " << 9 << '\n'
                << R1::at<0>::value << " " << R1::at<1>::value << '\n';

    using R2 = twosum<
        20,
        util::value_list<int, 1, 3, 5, 7, 9, 11, 13>
    >::result;
    static_assert(R2::size == 2, "Failure");
    static_assert(R2::at<0>::value + R2::at<1>::value == 20, "Failure");
    std::cout << "Target: " << 20 << '\n'
                << R2::at<0>::value << " " << R2::at<1>::value << '\n';

    using R3 = twosum<
        10,
        util::value_list<int, 5, 5, 7, 8>
    >::result;
    static_assert(R3::size == 2, "Failure");
    static_assert(R3::at<0>::value + R3::at<1>::value == 10, "Failure");
    std::cout << "Target: " << 10 << '\n'
                << R3::at<0>::value << " " << R3::at<1>::value << '\n';

    using R4 = twosum<
        0,
        util::value_list<int, -5, -2, 3, 5, 10>
    >::result;
    static_assert(R4::size == 2, "Failure");
    static_assert(R4::at<0>::value + R4::at<1>::value == 0, "Failure");
    std::cout << "Target: " << 0 << '\n'
                << R4::at<0>::value << " " << R4::at<1>::value << '\n';

    // No solution
    using R5 = twosum<
        100,
        util::value_list<int, 1, 2, 3, 4, 5>
    >::result;
    static_assert(R5::empty, "Failure");

    // Single element cannot form a pair
    using R6 = twosum<
        5,
        util::value_list<int, 5>
    >::result;
    static_assert(R6::empty, "Failure");

    // Empty list
    using R7 = twosum<
        5,
        util::value_list<int>
    >::result;
    static_assert(R7::empty, "Failure");

    return 0;
}