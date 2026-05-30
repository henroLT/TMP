#include <utility>
#include <concepts>
#include <cstddef>

// non-specialized 
template <typename... Ts>
struct all_unique;

// specialized, uses folds/recursion to compare all types
template <typename FirstType, typename... OtherTypes>
struct all_unique<FirstType, OtherTypes...> 
{
    static constexpr bool value = (!std::same_as<FirstType, OtherTypes> && ...)
                                    && all_unique<OtherTypes...>::value;
};

// default for empty typeset
template <>
struct all_unique<> 
{
    static constexpr bool value = true;
};

// typeset is and should be a single type...
template <typename... Ts>
constexpr bool is_type_set_v = false;

// forward declare removal
template <typename TypeSet, typename RemoveType, typename... Types>
struct type_set_remove_impl;

// check uniqueness
template <typename... Ts>
static constexpr bool all_unique_v = all_unique<Ts...>::value;



// A set of types
template <typename... Ts>
    requires all_unique_v<Ts...>
struct type_set 
{

    static constexpr std::size_t size = sizeof...(Ts);
    static constexpr bool empty = false;

    // fold to compare all types to SearchType
    template <typename SearchType>
    static constexpr bool contains = (std::same_as<SearchType, Ts> || ...);
    
    // create a new typeset with InsertType
    template <typename InsertType>
    using insert = type_set<Ts..., InsertType>;

    // create a new typeset without RemoveType
    template <typename RemoveType>
    using remove = typename type_set_remove_impl<type_set<>, RemoveType, Ts...>::type;
};

// An specialized empty version of typeset (see remove L.55)
template <>
struct type_set<> 
{
    static constexpr std::size_t size = 0;
    static constexpr bool empty = true;

    template <typename SearchType>
    static constexpr bool contains = false;

    template <typename InsertType>
    using insert = type_set<InsertType>;
};



template <typename... Ts>
constexpr bool is_type_set_v<type_set<Ts...>> = true;

// Recursively create new typeset without RemoveType
template <typename AccumTypes, typename RemoveType, typename FirstType, typename... OtherTypes>
    requires is_type_set_v<AccumTypes>
struct type_set_remove_impl<AccumTypes, RemoveType, FirstType, OtherTypes...> 
{
    using next = std::conditional_t<
                    !std::same_as<RemoveType, FirstType>,
                    typename AccumTypes::template insert<FirstType>,
                    AccumTypes
                >;
    
    // obtain the new typeset
    using type = typename type_set_remove_impl<next, RemoveType, OtherTypes...>::type;
};

// Empty case
template <typename AccumTypes, typename RemoveType>
    requires is_type_set_v<AccumTypes>
struct type_set_remove_impl<AccumTypes, RemoveType> 
{
    using type = AccumTypes;
};