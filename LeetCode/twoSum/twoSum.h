#ifndef twoSum_twoSum_h
#define twoSum_twoSum_h

#include <type_traits>
#include "Util/value_list.h"

// Two Sum
template <int Val, typename List>
struct twosum;

template <int Val>
struct twosum <Val, util::value_list<int>>
{
   using result = util::value_list<int>;
};

template <int Sum, int Head, int... Tail>
struct twosum <Sum, util::value_list<int, Head, Tail...>>
{
   using result = typename std::conditional<
      util::value_list<int, Tail...>::template contains<Sum - Head>::value,
      util::value_list<int, Head, Sum - Head>,
      typename twosum<
         Sum,
         util::value_list<int, Tail...>
      >::result
   >::type;
};

#endif
