#include <type_traits>
// result
template <int A, int B>
struct Result {
   static constexpr int first = A;
   static constexpr int second = B;
};
struct NoResult{};

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
struct twosum<Val, type_list<>>
{
   static constexpr bool found = false;
   using result = NoResult;
};

template <int Sum, int Head, int... Tail>
struct twosum<Sum, type_list<Head, Tail...>>
{
private:
   static constexpr bool here =
      contains<Sum - Head, type_list<Tail...>>::value;

public:
   static constexpr bool found =
      here || twosum<Sum, type_list<Tail...>>::found;
   
   using result = typename std::conditional<
      here,
      Result<Head, Sum - Head>,
      typename twosum<Sum, type_list<Tail...>>::result
   >::type;
};