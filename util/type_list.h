#ifndef util_type_list_h
#define util_type_list_h

#include <type_traits>
#include <cstddef>

/*
    * value_list
    *
    * Operations:
    *   size:            Number of elements.
    *   empty:           Whether the list is empty.
    *   contains<Val>:   Whether Val is in the list.
    *   append<Val>:     Appends Val to the end.
    *   remove<Val>:     Removes the first occurrence of Val.
    *   remove_all<Val>: Removes all occurrences of Val.
    *   at<Idx>:         Retrieves the value at index Idx.
    *                    at<Idx> is only valid for valid indices.
    *
    * For value_list<>:
    *   typeify<T>:     Converts an unspecified value_list to value_list<T>.
*/

namespace util {

template <typename... Ts>
struct type_list;

namespace detail {

// Contains
template <typename T, typename List>
struct type_list_contains;

template <typename T>
struct type_list_contains<T, type_list<>> : 
    std::false_type {};

template <typename T, typename Head, typename... Tail>
struct type_list_contains<T, type_list<Head, Tail...>> :
    std::conditional<
        std::is_same<T, Head>::value,
        std::true_type,
        type_list_contains<T, type_list<Tail...>>
    >::type
{};


// Remove First Occurance
template <typename T, typename List, typename Acc = type_list<>>
struct type_list_remove;

template <typename T, typename... Acc>
struct type_list_remove<T, type_list<>, type_list<Acc...>>
{
    using type = type_list<Acc...>;
};

template <typename T, typename... Tail, typename... Acc>
struct type_list_remove<T, type_list<T, Tail...>, type_list<Acc...>>
{
    using type = type_list<Acc..., Tail...>;
};

template <typename T, typename Head, typename... Tail, typename... Acc>
struct type_list_remove<T, type_list<Head, Tail...>, type_list<Acc...>> :
    type_list_remove<T, type_list<Tail...>, type_list<Acc..., Head>>
{};


// Remove All Occurance
template <typename T, typename List, typename Acc = type_list<>>
struct type_list_remove_all;

template <typename T, typename... Acc>
struct type_list_remove_all<T, type_list<>, type_list<Acc...>>
{
    using type = type_list<Acc...>;
};

template <typename T, typename... Tail, typename... Acc>
struct type_list_remove_all<T, type_list<T, Tail...>, type_list<Acc...>> :
    type_list_remove_all<T, type_list<Tail...>, type_list<Acc...>>
{};

template <typename T, typename Head, typename... Tail, typename... Acc>
struct type_list_remove_all<T, type_list<Head, Tail...>, type_list<Acc...>> :
    type_list_remove_all<T, type_list<Tail...>, type_list<Acc..., Head>>
{};


// At
template <std::size_t Target, typename List>
struct type_list_at;

template <typename Head, typename... Tail>
struct type_list_at<0, type_list<Head, Tail...>>
{
    using type = Head;
};

template <std::size_t Target, typename Head, typename... Tail>
struct type_list_at<Target, type_list<Head, Tail...>> :
    type_list_at<Target - 1, type_list<Tail...>>
{};

} // namespace detail





// Type List
template <typename... Ts>
struct type_list
{
    static constexpr std::size_t size = sizeof...(Ts);
    static constexpr bool empty = false;

    template <typename Elem>
    static constexpr bool contains = detail::type_list_contains<
        Elem, type_list<Ts...>
    >::value;

    template <typename Elem>
    using append = type_list<Ts..., Elem>;

    template <typename Elem>
    using remove = detail::type_list_remove<
        Elem, type_list<Ts...>
    >::type;

    template <typename Elem>
    using remove_all = detail::type_list_remove_all<
        Elem, type_list<Ts...>
    >::type;

    template <std::size_t Idx>
    using at = detail::type_list_at<
        Idx, type_list<Ts...>
    >::type;
};

// Empty Type List
template <>
struct type_list<>
{
    static constexpr std::size_t size = 0;
    static constexpr bool empty = true;

    template <typename Search>
    static constexpr bool contains = false;

    template <typename Elem>
    using append = type_list<Elem>;

    template <typename Elem>
    using remove = type_list<>;
    
    template <typename Elem>
    using remove_all = type_list<>;
};

} // namespace util

#endif
