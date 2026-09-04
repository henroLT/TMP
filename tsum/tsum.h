#include <type_traits>

// type list
template <int... Values>
struct type_list {};

// contains
template <int Val, typename List>
struct contains;

template <int Val>
struct contains<Val, type_list<>> : std::false_type {};

template <int Val, int Head, int... Tail>
struct contains<Val, type_list<Head, Tail...>>
   : std::conditional<
      Val == Head,
      std::true_type,
      contains<Val, type_list<Tail...>>
   >::type
{};


// compute
template <int Val, typename List>
struct twosum;

template <int Val>
struct twosum<Val, type_list<>> : std::false_type {};

template <int Sum, int Head, int... Tail>
struct twosum<Sum, type_list<Head, Tail...>>
   : std::conditional<
      contains<Sum - Head, type_list<Tail...>>::value,
      std::true_type,
      twosum<Sum, type_list<Tail...>>
   >::type
{};