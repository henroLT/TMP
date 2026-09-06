#ifndef threeSum_threeSum_h
#define threeSum_threeSum_h

#include <type_traits>
#include "Util/type_list.h"
#include "Util/value_list.h"

// three_sum inner
template <int Val, int A, typename List, typename Acc>
struct three_sum_inner;

template <int Val, int A, typename Acc>
struct three_sum_inner<Val, A, util::value_list<int>, Acc>
{
    using result = Acc;
};

template <int Val, int A, int B, int... Tail, typename Acc>
struct three_sum_inner<Val, A, util::value_list<int, B, Tail...>, Acc>
{
private:
    static constexpr int C = Val - A - B;
    static constexpr bool Exists =
        util::value_list<int, Tail...>::template contains<C>;
    
    using Triple = util::value_list<int, A, B, C>;
    using New_Acc = typename std::conditional<
        Exists && !Acc::template contains<Triple>,
        typename Acc::template append<Triple>,
        Acc
    >::type;

public:
    using result = typename three_sum_inner<
        Val,
        A,
        util::value_list<int, Tail...>,
        New_Acc
    >::result;
};


// three_sum
template <int Val, typename List, typename Acc = util::type_list<>>
struct three_sum;

template <int Val, typename Acc>
struct three_sum<Val, util::value_list<int>, Acc>
{
    using result = Acc;
};

template <int Val, int A, int... Tail, typename Acc>
struct three_sum<Val, util::value_list<int, A, Tail...>, Acc>
{
    using result = typename three_sum<
        Val,
        util::value_list<int, Tail...>,
        typename three_sum_inner<
            Val,
            A,
            util::value_list<int, Tail...>,
            Acc
        >::result
    >::result;
};

#endif
