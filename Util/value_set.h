#ifndef util_value_list_h
#define util_value_list_h

#include <type_traits>
#include <cstddef>

namespace util {

template <typename T = void, T... Ts>
struct value_set;

namespace detail {

// Contains
template <typename T, T Elem, typename List>
struct value_set_contains;

template <typename T, T Elem>
struct value_set_contains<T, Elem, value_set<T>> :
    std::false_type
{};

template <typename T, T Elem, T Head, T... Tail>
struct value_set_contains<T, Elem, value_set<T, Head, Tail...>> :
    std::conditional<
        Elem == Head,
        std::true_type,
        value_set_contains<
            T,
            Elem,
            value_set<T, Tail...>
        >
    >::type
{};


// Remove
template <typename T, T Elem, typename List, typename Acc = value_set<T>>
struct value_set_remove;

template <typename T, T Elem, T... Acc>
struct value_set_remove<T, Elem, value_set<T>, value_set<T, Acc...>>
{
    using type = value_set<T, Acc...>;
};

template <typename T, T Elem, T... Tail, T... Acc>
struct value_set_remove<T, Elem, value_set<T, Elem, Tail...>, value_set<T, Acc...>>
{
    using type = value_set<T, Acc..., Tail...>;
};

template <typename T, T Elem, T Head, T... Tail, T... Acc>
struct value_set_remove<T, Elem, value_set<T, Head, Tail...>, value_set<T, Acc...>> :
    value_set_remove<T, Elem, value_set<T, Tail...>, value_set<T, Acc...>>
{};


// At
template <std::size_t Target, typename List>
struct value_set_at;

template <typename T, T Head, T... Tail>
struct value_set_at<0, value_set<T, Head, Tail...>>
{
    static constexpr T value = Head;
};

template <std::size_t Target, typename T, T Head, T... Tail>
struct value_set_at<Target, value_set<T, Head, Tail...>> :
    value_set_at<Target - 1, value_set<T, Tail...>>
{};


// All Unique (for explict construction)
template <typename T, T... Ts>
struct value_set_is_unique;

template <typename T>
struct value_set_is_unique<T> :
    std::true_type
{};

template <typename T, T Head, T... Tail>
struct value_set_is_unique<T, Head, Tail...> :
    std::integral_constant<
        bool,
        !value_set_contains<
            T,
            Head,
            value_set<T, Tail...>
        >::value
        &&
        value_set_is_unique<
            T, 
            Tail...
        >::value
    >
{};

} // namespace detail





// Value Set
template <typename T, T... Ts>
struct value_set
{
    static_assert(detail::value_set_is_unique<T, Ts...>::value,
        "value_set cannot contain duplicates.");
    static constexpr std::size_t size = sizeof...(Ts);
    static constexpr bool empty = (sizeof...(Ts) == 0);

    template <T Elem>
    static constexpr bool contains = detail::value_set_contains<
        T,
        Elem,
        value_set<T, Ts...>
    >::value;

    template <std::size_t Idx>
    static constexpr T at = detail::value_set_at<
        Idx,
        value_set<T, Ts...>
    >::value;

    template <T Elem>
    using remove = detail::value_set_remove<
        T,
        Elem,
        value_set<T, Ts...>
    >::type;

    template <T Elem>
    using append = std::conditional<
        detail::value_set_contains<T, Elem, value_set<T, Ts...>>::value,
        value_set<T, Ts...>,
        value_set<T, Ts..., Elem>
    >::type;
};

template <>
struct value_set<>
{
    template <typename T>
    using typeify = value_set<T>;
};

} // namespace util

#endif
