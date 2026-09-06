#include "threeSum/threeSum.h"

#include <iostream>
#include <type_traits>

namespace {

template <typename List>
struct print_triples;

template <>
struct print_triples<util::type_list<>>
{
    static void print() {}
};

template <typename Triple, typename... Tail>
struct print_triples<util::type_list<Triple, Tail...>>
{
    static void print()
    {
        std::cout << Triple::template at<0> << " "
                  << Triple::template at<1> << " "
                  << Triple::template at<2> << '\n';
        print_triples<util::type_list<Tail...>>::print();
    }
};

} // namespace anonymous

int main()
{
    // Triple testing
    using R1 = three_sum<
        9,
        util::value_list<int, 1, 2, 3, 4, 5, 6, 7>
    >::result;
    static_assert(R1::size == 3, "Failure");
    static_assert(R1::contains<util::value_list<int, 1, 2, 6>>, "Failure");
    static_assert(R1::contains<util::value_list<int, 1, 3, 5>>, "Failure");
    static_assert(R1::contains<util::value_list<int, 2, 3, 4>>, "Failure");
    std::cout << "Target: 9\n";
    print_triples<R1>::print();

    using R2 = three_sum<
        10,
        util::value_list<int, 1, 2, 3, 5, 7, 8>
    >::result;
    static_assert(R2::size == 2, "Failure");
    static_assert(R2::contains<util::value_list<int, 1, 2, 7>>, "Failure");
    static_assert(R2::contains<util::value_list<int, 2, 3, 5>>, "Failure");
    std::cout << "Target: 10\n";
    print_triples<R2>::print();

    using R3 = three_sum<
        10,
        util::value_list<int, 5, 5, 7, 8, -3, -2>
    >::result;
    static_assert(R3::size == 2, "Failure");
    static_assert(R3::contains<util::value_list<int, 5, 8, -3>>, "Failure");
    static_assert(R3::contains<util::value_list<int, 5, 7, -2>>, "Failure");
    std::cout << "Target: 10\n";
    print_triples<R3>::print();


    using R4 = three_sum<
        0,
        util::value_list<int, -5, -2, 0, 2, 5, 7>
    >::result;
    static_assert(R4::size == 3, "Failure");
    static_assert(R4::contains<util::value_list<int, -5, -2, 7>>, "Failure");
    static_assert(R4::contains<util::value_list<int, -5, 0, 5>>, "Failure");
    static_assert(R4::contains<util::value_list<int, -2, 0, 2>>, "Failure");
    std::cout << "Target: 0\n";
    print_triples<R4>::print();

    // No solution
    using R5 = three_sum<
        100,
        util::value_list<int, 1, 2, 3, 4, 5>
    >::result;
    static_assert(R5::empty, "Failure");

    // Fewer than three elements
    using R6 = three_sum<
        5,
        util::value_list<int, 5, 1>
    >::result;
    static_assert(R6::empty, "Failure");

    // Empty list
    using R7 = three_sum<
        5,
        util::value_list<int>
    >::result;
    static_assert(R7::empty, "Failure");

    return 0;
}