#ifndef twoSum_twoSum
#define twoSum_twoSum

#include <type_traits>
#include "util/value_list.h"

// result
template <int A, int B>
struct Result {
   static constexpr int first = A;
   static constexpr int second = B;
};
struct NoResult{};

// Two Sum
template <int Val, typename List>
struct twosum;

template <int Val>
struct twosum<Val, value_list<int>>
{
   static constexpr bool found = false;
   using result = NoResult;
};

template <int Sum, int Head, int... Tail>
struct twosum<Sum, value_list<int, Head, Tail...>>
{
private:
   static constexpr bool here =
      value_list<int, Tail...>::template contains<Sum - Head>;

public:
   static constexpr bool found =
      here || twosum<Sum, value_list<int, Tail...>>::found;
   
   using result = typename std::conditional<
      here,
      Result<Head, Sum - Head>,
      typename twosum<Sum, value_list<int, Tail...>>::result
   >::type;
};

#endif
