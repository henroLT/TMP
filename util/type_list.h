#ifndef util_type_list
#define util_type_list

#include <type_traits>
#include <cstddef>

template <typename... Ts>
struct type_list;

namespace detail {

// Contains
template <typename T, typename List>
struct contains;

template <typename T>
struct contains<T, type_list<>> : 
    std::false_type {};

template <typename T, typename Head, typename... Tail>
struct contains<T, type_list<Head, Tail...>> :
    std::conditional<
        std::is_same<T, Head>::value,
        std::true_type,
        contains<T, type_list<Tail...>>
    >::type
{};


// Remove First Occurance
template <typename T, typename List, typename Acc = type_list<>>
struct remove;

template <typename T, typename... Acc>
struct remove<T, type_list<>, type_list<Acc...>>
{
    using type = type_list<Acc...>;
};

template <typename T, typename... Tail, typename... Acc>
struct remove<T, type_list<T, Tail...>, type_list<Acc...>>
{
    using type = type_list<Acc..., Tail...>;
};

template <typename T, typename Head, typename... Tail, typename... Acc>
struct remove<T, type_list<Head, Tail...>, type_list<Acc...>> :
    remove<T, type_list<Tail...>, type_list<Acc..., Head>>
{};


// Remove All Occurance
template <typename T, typename List, typename Acc = type_list<>>
struct remove_all;

template <typename T, typename... Acc>
struct remove_all<T, type_list<>, type_list<Acc...>>
{
    using type = type_list<Acc...>;
};

template <typename T, typename... Tail, typename... Acc>
struct remove_all<T, type_list<T, Tail...>, type_list<Acc...>> :
    remove_all<T, type_list<Tail...>, type_list<Acc...>>
{};

template <typename T, typename Head, typename... Tail, typename... Acc>
struct remove_all<T, type_list<Head, Tail...>, type_list<Acc...>> :
    remove_all<T, type_list<Tail...>, type_list<Acc..., Head>>
{};

} // namespace detail





// Type List
template <typename... Ts>
struct type_list
{
    static constexpr std::size_t size = sizeof...(Ts);
    static constexpr bool empty = false;

    template <typename Elem>
    static constexpr bool contains = detail::contains<
        Elem, type_list<Ts...>
    >::value;

    template <typename Elem>
    using append = type_list<Ts..., Elem>;

    template <typename Elem>
    using remove = detail::remove<
        Elem, type_list<Ts...>
    >::type;

    template <typename Elem>
    using remove_all = detail::remove_all<
        Elem, type_list<Ts...>
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

#endif
