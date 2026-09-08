#ifndef util_value_list_h
#define util_value_list_h

#include <type_traits>
#include <cstddef>

/*
    * value_list
    *
    * Compile time list of values for type T
    *
    * Operations:
    *   size:             Number of elements.
    *   empty:            Whether the list is empty.
    *   contains<Val>:    Whether Val occurs in the list.
    *   append<Val>:      Appends Val to the end.
    *   remove<Val>:      Removes the first occurrence of Val.
    *   remove_all<Val>:  Removes all occurrences of Val.
    *   at<Idx>:          Retrieves the value at index Idx.
    *                     Only valid for valid indexs
    *
    * value_list<> represents an untyped list
    *   must use typeify<T> to create a typed value_list.
    *
*/

namespace util {

template <typename T = void, T... Ts>
struct value_list;

namespace detail {

// Contains
template <typename T, T Elem, typename List>
struct value_list_contains;

template <typename T, T Elem>
struct value_list_contains<T, Elem, value_list<T>> :
    std::false_type {};

template <typename T, T Elem, T Head, T... Tail>
struct value_list_contains<T, Elem, value_list<T, Head, Tail...>> :
    std::conditional<
        Elem == Head,
        std::true_type,
        value_list_contains<
            T,
            Elem,
            value_list<T, Tail...>
        >
    >::type
{};


// Remove
template <typename T, T Elem, typename List, typename Acc = value_list<T>>
struct value_list_remove;

template <typename T, T Elem, T... Acc>
struct value_list_remove<T, Elem, value_list<T>, value_list<T, Acc...>>
{
    using type = value_list<T, Acc...>;
};

template <typename T, T Elem, T... Tail, T... Acc>
struct value_list_remove<T, Elem, value_list<T, Elem, Tail...>, value_list<T, Acc...>>
{
    using type = value_list<T, Acc..., Tail...>;
};

template <typename T, T Elem, T Head, T... Tail, T... Acc>
struct value_list_remove<T, Elem, value_list<T, Head, Tail...>, value_list<T, Acc...>> :
    value_list_remove<T, Elem, value_list<T, Tail...>, value_list<T, Acc..., Head>>
{};


// Remove All
template <typename T, T Elem, typename List, typename Acc = value_list<T>>
struct value_list_remove_all;

template <typename T, T Elem, T... Acc>
struct value_list_remove_all<T, Elem, value_list<T>, value_list<T, Acc...>>
{
    using type = value_list<T, Acc...>;
};

template <typename T, T Elem, T... Tail, T... Acc>
struct value_list_remove_all<T, Elem, value_list<T, Elem, Tail...>, value_list<T, Acc...>> :
    value_list_remove_all<T, Elem, value_list<T, Tail...>, value_list<T, Acc...>>
{};

template <typename T, T Elem, T Head, T... Tail, T... Acc>
struct value_list_remove_all<T, Elem, value_list<T, Head, Tail...>, value_list<T, Acc...>> :
    value_list_remove_all<T, Elem, value_list<T, Tail...>, value_list<T, Acc..., Head>>
{};


// At
template <std::size_t Target, typename List>
struct value_list_at;

template <typename T, T Head, T... Tail>
struct value_list_at<0, value_list<T, Head, Tail...>> :
    std::integral_constant<T, Head>
{};

template <std::size_t Target, typename T, T Head, T... Tail>
struct value_list_at<Target, value_list<T, Head, Tail...>> :
    value_list_at<Target - 1, value_list<T, Tail...>>
{};

} // namespace detail





// Value List
template <typename T, T... Ts>
struct value_list
{
    static constexpr std::size_t size = sizeof...(Ts);
    static constexpr bool empty = (sizeof...(Ts) == 0);

    template <T Elem>
    using append = value_list<T, Ts..., Elem>;

    template <T Elem>
    using contains = detail::value_list_contains<
        T,
        Elem,
        value_list<T, Ts...>
    >;

    template <T Elem>
    using remove = typename detail::value_list_remove<
        T,
        Elem,
        value_list<T, Ts...>
    >::type;

    template <T Elem>
    using remove_all = typename detail::value_list_remove_all<
        T,
        Elem,
        value_list<T, Ts...>
    >::type;

    template <std::size_t Idx>
    using at = detail::value_list_at<
        Idx,
        value_list<T, Ts...>
    >;
};

// Unspecified Value List
// Illegal to preform any modifier besides typeify
template <>
struct value_list<>
{
    template <typename T>
    using typeify = value_list<T>;
};

} // namespace util

#endif
