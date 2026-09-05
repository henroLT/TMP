#ifndef util_value_list
#define util_value_list

#include <type_traits>
#include <cstddef>

template <typename T = void, T... Ts>
struct value_list;

namespace detail {

// Contains
template <typename T, T Elem, typename List>
struct contains;

template <typename T, T Elem>
struct contains<T, Elem, value_list<T>> :
    std::false_type {};

template <typename T, T Elem, T Head, T... Tail>
struct contains<T, Elem, value_list<T, Head, Tail...>> :
    std::conditional<
        Elem == Head,
        std::true_type,
        contains<T, Elem, value_list<T, Tail...>>
    >::type
{};


// Remove
template <typename T, T Elem, typename List, typename Acc = value_list<T>>
struct remove;

template <typename T, T Elem, T... Acc>
struct remove<T, Elem, value_list<T>, value_list<T, Acc...>>
{
    using type = value_list<T, Acc...>;
};

template <typename T, T Elem, T... Tail, T... Acc>
struct remove<T, Elem, value_list<T, Elem, Tail...>, value_list<T, Acc...>>
{
    using type = value_list<T, Acc..., Tail...>;
};

template <typename T, T Elem, T Head, T... Tail, T... Acc>
struct remove<T, Elem, value_list<T, Head, Tail...>, value_list<T, Acc...>> :
    remove<T, Elem, value_list<T, Tail...>, value_list<T, Acc..., Head>>
{};


// Remove All
template <typename T, T Elem, typename List, typename Acc = value_list<T>>
struct remove_all;

template <typename T, T Elem, T... Acc>
struct remove_all<T, Elem, value_list<T>, value_list<T, Acc...>>
{
    using type = value_list<T, Acc...>;
};

template <typename T, T Elem, T... Tail, T... Acc>
struct remove_all<T, Elem, value_list<T, Elem, Tail...>, value_list<T, Acc...>> :
    remove_all<T, Elem, value_list<T, Tail...>, value_list<T, Acc...>>
{};

template <typename T, T Elem, T Head, T... Tail, T... Acc>
struct remove_all<T, Elem, value_list<T, Head, Tail...>, value_list<T, Acc...>> :
    remove_all<T, Elem, value_list<T, Tail...>, value_list<T, Acc..., Head>>
{};

} // namespace detail





// Value List
template <typename T, T... Ts>
struct value_list
{
    static constexpr std::size_t size = sizeof...(Ts);
    static constexpr bool empty = false;

    template <T Elem>
    static constexpr bool contains = detail::contains<
        T, Elem, value_list<T, Ts...>
    >::value;

    template <T Elem>
    using remove = detail::remove<T, Elem, value_list<T, Ts...>>::type;

    template <T Elem>
    using remove_all = detail::remove_all<T, Elem, value_list<T, Ts...>>::type;

    template <T Elem>
    using append = value_list<T, Ts..., Elem>;
};

// Empty Value List
template <typename T>
struct value_list<T>
{
    static constexpr std::size_t size = 0;
    static constexpr bool empty = true;

    template <T Elem>
    static constexpr bool contains = false;

    template <T Elem>
    using remove = value_list<T>;

    template <T Elem>
    using remove_all = value_list<T>;

    template <T Elem>
    using append = value_list<T, Elem>;
};

// Unspecified Value List
// Illegal to preform any modifier besides typeify
template <>
struct value_list<>
{
    template <typename T>
    using typeify = value_list<T>;
};

#endif
